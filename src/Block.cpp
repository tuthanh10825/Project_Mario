#include "Block.h"

Block::Block(TextureHolder& textures, Textures::ID blockID) : Entity(), sprite(textures.get(blockID))
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


