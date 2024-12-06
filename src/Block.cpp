#include "Block.h"

Block::Block(sf::Texture& texture) : Entity(), sprite(texture)
{
}

void Block::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned Block::getCategory() const
{
	return Category::Block;
}

sf::FloatRect Block::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}


