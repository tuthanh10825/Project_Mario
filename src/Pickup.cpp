#include "Pickup.h"
#include "Utility.h"

Pickup::Pickup(Type type, TextureHolder& textures)
	: Entity(1)
	, type(type)
	, mov(false)
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
	
	animation.setFrameSize(sf::Vector2i(60, 60));
	animation.setNumFrames(5);
	animation.setDuration(sf::seconds(0.8));
	animation.setRepeating(true);

	centerOrigin(animation);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mov)
		target.draw(animation, states);
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
	if (mov) {
		// set the position of the animation here
		animation.update(dt);
	}
	Entity::updateCurrent(dt);
}

void Pickup::setMove(bool isMove)
{
	mov = isMove;
}

void Pickup::apply(Character& character) const
{
	// apply the effect of the pickup to the character
	switch (type)
	{
	case Pickup::mushroom:
		break;
	case Pickup::coin:
		break;
	case Pickup::fireFlower:
		break;
	default:
		break;
	}
}

