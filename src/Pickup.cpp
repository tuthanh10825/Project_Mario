#include "Pickup.h"
#include "Utility.h"
#include "Character.h"
#include "DataTable.h"

namespace {
	const std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(Type type, TextureHolder& textures)
	: Entity(1)
	, type(type)
	, moveLeft(false)
	, moveRight(false)
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
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{ 
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
	if (type == Pickup::Type::Mushroom)
	{
		sf::Vector2f curVecl = getVelocity();
		if (moveRight && !moveLeft)
		{
			this->setVelocity(80.f, curVecl.y);
		}
		else if (moveLeft && !moveRight)
		{
			this->setVelocity(-80.f, curVecl.y);
		}
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
	Table[type].action(character);
}

