#include "Character.h"
#include "Utility.h"
#include "DataTable.h"
#include <iostream>

namespace {
	const std::vector<CharacterData> Table = initializeCharacterData();
}

Character::Character(Type type, TextureHolder& textures) 
	: Entity(1)
	, type(type)
	, mMovRight(textures.get(Table[type].movRight))
	, mMovLeft(textures.get(Table[type].movLeft))
	, moveLeft(false)
	, moveRight(false)
	, jump(false)
	, jumpCount(0)
	, fire(false)
	, mFireCountdown(sf::Time::Zero)
	, direction(1)
	, point(0)
	, hasFireFlower(true)
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

	mMovRight.setFrameSize(sf::Vector2i(36, 72));
	mMovRight.setNumFrames(5);
	mMovRight.setDuration(sf::seconds(0.8));
	mMovRight.setRepeating(true);



	centerOrigin(mMovRight);

	mMovLeft.setFrameSize(sf::Vector2i(36, 72));
	mMovLeft.setNumFrames(5);
	mMovLeft.setDuration(sf::seconds(0.8));
	mMovLeft.setRepeating(true);

	centerOrigin(mMovLeft);

	this->setAcceleration(0, 200);

	mFireCommand.category = Category::SceneNodeAir;
	mFireCommand.action = [this, &textures](SceneNode& node, sf::Time dt) {
		sf::Vector2f pos = getWorldPosition();
		pos.y += 12.f;
		createProjectile(node, textures, pos, Projectile::CharBullet);
		fire = false;
		mFireCountdown = sf::seconds(1.f);
		};
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (moveRight && !moveLeft) {
		target.draw(mMovRight, states);
	}
	else if (moveLeft && !moveRight) {
		target.draw(mMovLeft, states);
	}
	else target.draw(sprite, states);
}

unsigned Character::getCategory() const
{
	return Category::Player;
}

sf::FloatRect Character::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Character::updateCurrent(sf::Time dt)
{
	//Handle Animation
	if (moveRight && !moveLeft) {
		if (direction == -1) {
			sprite.scale(-1.f, 1.f);
			direction = 1;
		}
		mMovRight.update(dt);
	}
	else if (moveLeft) {
		if (direction == 1) {
			sprite.scale(-1.f, 1.f);
			direction = -1;
		}
		mMovLeft.update(dt);
	}
	
	if (mFireCountdown <= sf::Time::Zero)
		mFireCountdown = sf::Time::Zero;
	else if (mFireCountdown > sf::Time::Zero)
		mFireCountdown -= dt;
	Entity::updateCurrent(dt);
}

void Character::setMoveLeft(bool isMove)
{
	moveLeft = isMove; 
}

void Character::setMoveRight(bool isMove)
{
	moveRight = isMove; 
}

void Character::setJump(bool isJump)
{
	this -> jump = isJump;
}
void Character::incrJump()
{
	++jumpCount;
}
short Character::countJump()
{
	return jumpCount; 
}
void Character::resetJump()
{
	jumpCount = 0; 
}
bool Character::isMoveLeft() const
{
	return this -> moveLeft;
}

bool Character::isMoveRight() const
{
	return this -> moveRight;
}

bool Character::isJump() const
{
	return this->jump;
}

void Character::createProjectile(SceneNode& node, TextureHolder& textures, sf::Vector2f pos, Projectile::Type type)
{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));
	projectile->setPosition(pos);
	projectile->setVelocity(400.f * direction, 0.f);
	node.attachChild(std::move(projectile));
}

void Character::setFire(bool fire)
{
	this->fire = fire;
}

bool Character::isFire() const
{
	return (fire == 0) && mFireCountdown == sf::Time::Zero;
}

Command Character::getFireCommand()
{
	return mFireCommand;
}

bool Character::canFire() const {
	return (fire == 1) && (mFireCountdown == sf::Time::Zero);
}

void Character::incrPoint(int point)
{
	this->point += point;
}

int Character::getPoint() const
{
	return point;
}

bool Character::hasFire() const
{
	return hasFireFlower;
}

void Character::setHasFireFlower(bool hasFire)
{
	hasFireFlower = hasFire;
}
