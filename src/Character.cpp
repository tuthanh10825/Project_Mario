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
	, mMovement(textures.get(Textures::Movement))
	, moveLeft(false)
	, moveRight(false)
	, air(true)
{

	mMovement.setFrameSize(sf::Vector2i(128, 128));
	mMovement.setNumFrames(3);
	mMovement.setDuration(sf::seconds(0.3));
	mMovement.setRepeating(true);

	centerOrigin(mMovement);


	sf::FloatRect bound = sprite.getLocalBounds();
	sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	this->setAcceleration(0, 200);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (moveRight) {
		target.draw(mMovement, states);
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
	const float speed = 500.f;
	const float friction = 1000.f;	
	const float g = 1000.f;

	sf::Vector2f charVelocity = getVelocity();
	sf::Vector2f charAccel = getAcceleration();

	//Handle x speed
	if (moveLeft ^ moveRight) {
		if (moveLeft) {
			charVelocity.x = -speed; 
		}
		else {
			charVelocity.x = speed; 
		}
	}
	else {
		if (charVelocity.x > 1) {
			charAccel.x = -friction; 
		}
		else if (charVelocity.x < -1) {
			charAccel.x = friction; 
		}
		else {
			charAccel.x = 0; 
		}

	}
	//Handle y speed

	if (air) {
		charAccel.y = g;
	}

	else if (!air) {
		charAccel.y = 0; 
		charVelocity.y = 0; 
	}

	//Handle Animation
	
	if (moveRight) {
		mMovement.update(dt);
	}

	setVelocity(charVelocity); 
	setAcceleration(charAccel); 
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

void Character::setAir(bool isAir) 
{
	this -> air = isAir; 
}

bool Character::isAir() const
{
	return this -> air;
}


