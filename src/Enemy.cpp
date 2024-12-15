#include "Enemy.h"
#include "Utility.h"

static Textures::ID toTextureID(Enemy::Type type, Enemy::State state)
{
	switch (type)
	{
	case Enemy::Goomba:
		switch (state)
		{
		case Enemy::alive:
			return Textures::Goomba;
			break;
		case Enemy::movRight:
			return Textures::GoombaMovRight;
			break;
		case Enemy::movLeft:
			return Textures::GoombaMovLeft;
			break;
		case Enemy::die:
			return Textures::GoombaDead;
			break;
		default:
			break;
		}
		break;
	}
	return Textures::Goomba;
}

Enemy::Enemy(Type type, TextureHolder& textures)
	: Entity(1)
	, type(type)
	, mMovLeft(textures.get(toTextureID(type, Enemy::movLeft)))
	, mMovRight(textures.get(toTextureID(type, Enemy::movRight)))
	, mDead(textures.get(toTextureID(type, Enemy::die)))
	, moveLeft(true)
	, moveRight(false)
	, air(true)
	, showDead(true)
{
	sf::Texture& texture = textures.get(toTextureID(type, Enemy::alive));

	sf::Vector2u boundaryRect = texture.getSize();

	sprite.setTexture(&texture);
	sprite.setSize(sf::Vector2f(boundaryRect.x, boundaryRect.y));
	sprite.setOrigin(sf::Vector2f(boundaryRect.x / 2.f, boundaryRect.y / 2.f));

#if _DEBUG
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setOutlineThickness(-2);
#endif // _DEBUG

	mMovRight.setFrameSize(sf::Vector2i(48, 48));
	mMovRight.setNumFrames(2);
	mMovRight.setDuration(sf::seconds(0.8));
	mMovRight.setRepeating(true);

	centerOrigin(mMovRight);

	mMovLeft.setFrameSize(sf::Vector2i(48, 48));
	mMovLeft.setNumFrames(2);
	mMovLeft.setDuration(sf::seconds(0.8));
	mMovLeft.setRepeating(true);

	centerOrigin(mMovLeft);

	mDead.setFrameSize(sf::Vector2i(48, 24));
	mDead.setNumFrames(1);
	mDead.setDuration(sf::seconds(0.1));
	mDead.setRepeating(false);

	centerOrigin(mDead);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isDestroyed() && mDead.isFinished()) {
		return;
	}
	if (moveRight && !moveLeft) {
		target.draw(mMovRight, states);
	}
	else if (moveLeft && !moveRight) {
		target.draw(mMovLeft, states);
	}
	else if (isDestroyed() && showDead) {
		target.draw(sprite, states);
	}
	else target.draw(sprite, states);
}

unsigned Enemy::getCategory() const
{
	return Category::Enemy;
}

sf::FloatRect Enemy::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Enemy::updateCurrent(sf::Time dt)
{
	if (moveRight && !moveLeft) {
		this->setVelocity(100.f, 0);
		mMovRight.update(dt);
	}
	else if (moveLeft) {
		this->setVelocity(-100.f, 0);
		mMovLeft.update(dt);
	}
	else if (isDestroyed()) {
		mDead.update(dt);
		this->setVelocity(0, 0);
	}

	if (air) {
		this->setAcceleration(0,10000);
	}
	else {
		this->setAcceleration(0, 0);
	}
	Entity::updateCurrent(dt);
}

void Enemy::setMoveLeft(bool isMove)
{
	moveLeft = isMove;
}

void Enemy::setMoveRight(bool isMove)
{
	moveRight = isMove;
}

bool Enemy::isMoveLeft() const
{
	return moveLeft;
}

bool Enemy::isMoveRight() const
{
	return moveRight;
}


void Enemy::remove()
{
	Enemy::destroy();
	showDead = false;
}

bool Enemy::isMarkedForRemoval() const
{
	return isDestroyed() && mDead.isFinished();
}