#include "Enemy.h"
#include "Utility.h"
#include "DataTable.h"
#include <iostream>

namespace {
	const std::vector<EnemyData> Table = initializeEnemyData();
}

Enemy::Enemy(Type type, TextureHolder& textures)
	: Entity(Table[type].hp)
	, type(type)
	, mMovLU(textures.get(Table[type].movLU))
	, mMovRD(textures.get(Table[type].movRD))
	, mDead(textures.get(Table[type].dead))
	, moveLU(true)
	, moveRD(false)
	, showDead(true)
{
	sf::Texture& texture = textures.get(Table[type].texture);

	sf::Vector2u boundaryRect = texture.getSize();

	sprite.setTexture(&texture);
	sprite.setSize(sf::Vector2f(boundaryRect.x, boundaryRect.y));
	sprite.setOrigin(sf::Vector2f(boundaryRect.x / 2.f, boundaryRect.y / 2.f));

#if _DEBUG
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setOutlineThickness(-2);
#endif // _DEBUG

	mMovRD.setFrameSize(Table[type].frameSize);
	mMovRD.setNumFrames(2);
	mMovRD.setDuration(sf::seconds(0.8));
	mMovRD.setRepeating(true);

	centerOrigin(mMovRD);

	mMovLU.setFrameSize(Table[type].frameSize);
	mMovLU.setNumFrames(2);
	mMovLU.setDuration(sf::seconds(0.8));
	mMovLU.setRepeating(true);

	centerOrigin(mMovLU);

	mDead.setFrameSize(Table[type].frameSize);
	mDead.setNumFrames(1);
	mDead.setDuration(sf::seconds(0.2));
	mDead.setRepeating(false);

	centerOrigin(mDead);
	this->setVelocity(Table[type].speed);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isDestroyed() && mDead.isFinished()) {
		return;
	}
	if (isDestroyed() && showDead) {
		target.draw(sprite, states);
		return;
	}
	if (moveRD && !moveLU) {
		target.draw(mMovRD, states);
	}
	else if (moveLU && !moveRD) {
		target.draw(mMovLU, states);
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
	sf::Vector2f currVelo = getVelocity();
	sf::Vector2f pos = getWorldPosition();
	if (isDestroyed()) {
		mDead.update(dt);
		this->setVelocity(0, 0);
		Entity::updateCurrent(dt);
		return;
	}
	if (Table[type].isFly) {
		this->setAcceleration(0.f, 0.f);
		if (pos.y < origin.y - Table[type].range.y || pos.x < origin.x - Table[type].range.x) {
			std::cout << pos.y << " " << origin.y - Table[type].range.y << " " << pos.x << " " << origin.x - Table[type].range.x << std::endl;
			this->setVelocity(-Table[type].speed.x, -Table[type].speed.y);
			moveRD = true;
			moveLU = false;
		}
		else if (pos.y > origin.y + Table[type].range.y || pos.x > origin.x + Table[type].range.x) {
			this->setVelocity(Table[type].speed.x, Table[type].speed.y);
			moveLU = true;
			moveRD = false;
		}
		mMovRD.update(dt);
		mMovLU.update(dt);
	}
	else {
		if (moveRD && !moveLU) {
			this->setVelocity(Table[type].speed.x, currVelo.y);
			mMovRD.update(dt);
		}
		else if (moveLU) {
			this->setVelocity(-Table[type].speed.x, currVelo.y);
			mMovLU.update(dt);
		}
	}
	
	Entity::updateCurrent(dt);
}

void Enemy::setMoveLeft(bool isMove)
{
	moveLU = isMove;
}

void Enemy::setMoveRight(bool isMove)
{
	moveRD = isMove;
}

bool Enemy::isMoveLeft() const
{
	return moveLU;
}

bool Enemy::isMoveRight() const
{
	return moveRD;
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

void Enemy::setPosition(sf::Vector2f pos)
{
	origin = pos;
	Entity::setPosition(pos);
}

Enemy::Type Enemy::getType()
{
	return type;
}