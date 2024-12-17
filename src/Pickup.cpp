#include "Pickup.h"
#include "Utility.h"

Pickup::Pickup(Type type, TextureHolder& textures)
	: Entity(1)
	, type(type)
	, moveLeft(false)
	, moveRight(false)
	, mMovLeft(textures.get(Textures::Pickup))
	, mMovRight(textures.get(Textures::Pickup))
{
	sf::Texture& texture = textures.get(Textures::Pickup);
	sf::Vector2u boundaryRect = texture.getSize();
	sprite.setTexture(&texture);
	sprite.setSize(sf::Vector2f(boundaryRect.x, boundaryRect.y));
	sprite.setOrigin(sf::Vector2f(boundaryRect.x / 2.f, boundaryRect.y / 2.f));

#if _DEBUG
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setOutlineThickness(-2);
#endif // _DEBUG

	mMovRight.setFrameSize(sf::Vector2i(48, 48));
	mMovRight.setNumFrames(1);
	mMovRight.setDuration(sf::seconds(0.8));
	mMovRight.setRepeating(true);

	centerOrigin(mMovRight);

	mMovLeft.setFrameSize(sf::Vector2i(48, 48));
	mMovLeft.setNumFrames(1);
	mMovLeft.setDuration(sf::seconds(0.8));
	mMovLeft.setRepeating(true);

	centerOrigin(mMovLeft);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	if (moveRight && !moveLeft)
	{
		target.draw(mMovRight, states);
	}
	else if (moveLeft && !moveRight)
	{
		target.draw(mMovLeft, states);
	}
	else
	target.draw(sprite, states);
}

unsigned Pickup::getCategory() const
{
	return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Pickup::updateCurrent(sf::Time dt)
{
	sf::Vector2f curVecl = getVelocity();
	if (moveRight && !moveLeft)
	{
		this->setVelocity(80.f, curVecl.y);
		mMovRight.update(dt);
	}
	else if (moveLeft && !moveRight)
	{
		this->setVelocity(-80.f, curVecl.y);
		mMovLeft.update(dt);
	}
	Entity::updateCurrent(dt);
}

void Pickup::setMoveRight(bool isMove)
{
	moveRight = isMove;
}

void Pickup::setMoveLeft(bool isMove)
{
	moveLeft = isMove;
}

void Pickup::apply(Character& character) const
{
	// apply the effect of the pickup to the character
	switch (type)
	{
	case Pickup::mushroom:
		character.heal(1);
		break;
	case Pickup::coin:
		break;
	case Pickup::fireFlower:
		break;
	default:
		break;
	}
}

