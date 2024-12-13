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
	: Entity()
	, type(type)
	, mMovLeft(textures.get(toTextureID(type, Enemy::movLeft)))
	, mMovRight(textures.get(toTextureID(type, Enemy::movRight)))
	, moveLeft(true)
	, moveRight(false)
	, air(false)
	, dead(false)
{
	sf::Texture& texture = textures.get(toTextureID(type, Enemy::alive));

	sf::Vector2u boundaryRect = texture.getSize();

	sprite.setTexture(&texture);
	sprite.setSize(sf::Vector2f(boundaryRect.x, boundaryRect.y));
	sprite.setOrigin(sf::Vector2f(boundaryRect.x / 2.f, boundaryRect.y / 2.f));

	sf::Texture& deadTexture = textures.get(toTextureID(type, Enemy::die));

	sf::Vector2u deadBoundaryRect = deadTexture.getSize();

	deadSprite.setTexture(&deadTexture);
	deadSprite.setSize(sf::Vector2f(deadBoundaryRect.x, deadBoundaryRect.y));
	deadSprite.setOrigin(sf::Vector2f(deadBoundaryRect.x / 2.f, deadBoundaryRect.y / 2));

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
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (moveRight && !moveLeft) {
		target.draw(mMovRight, states);
	}
	else if (moveLeft && !moveRight) {
		target.draw(mMovLeft, states);
	}
	else if (dead) {
		target.draw(deadSprite, states);
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

	if (air) {
		this->setAcceleration(0, 9800);
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

void Enemy::setAir(bool isAir)
{
	air = isAir;
}

bool Enemy::isAir() const
{
	return air;
}

void Enemy::setDead(bool isDead)
{
	dead = isDead;
}

bool Enemy::isDead() const
{
	return dead;
}
