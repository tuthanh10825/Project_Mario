#include "Character.h"
#include "Utility.h"

static Textures::ID toTextureID(Character::Type type) {
	switch (type) {
	case Character::Character1:
		return Textures::Character1;
	}
}
Character::Character(Type type, const TextureHolder& textures) 
	: Entity()
	, type(type)
	, sprite(textures.get(toTextureID(type)))
	, mMovRight(textures.get(Textures::MovRight))
	, mMovLeft(textures.get(Textures::MovLeft))
	, moveLeft(false)
	, moveRight(false)
	, jump(false)
	, air(true)
{

	mMovRight.setFrameSize(sf::Vector2i(60, 120));
	mMovRight.setNumFrames(5);
	mMovRight.setDuration(sf::seconds(0.8));
	mMovRight.setRepeating(true);



	centerOrigin(mMovRight);

	mMovLeft.setFrameSize(sf::Vector2i(60, 120));
	mMovLeft.setNumFrames(5);
	mMovLeft.setDuration(sf::seconds(0.8));
	mMovLeft.setRepeating(true);

	centerOrigin(mMovLeft);


	sf::FloatRect bound = sprite.getLocalBounds();
	sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	this->setAcceleration(0, 200);
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
		mMovRight.update(dt);
	}
	else if (moveLeft) {
		mMovLeft.update(dt);
	}

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



void Character::setAir(bool isAir) 
{
	this -> air = isAir; 
}

bool Character::isAir() const
{
	return this -> air;
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


