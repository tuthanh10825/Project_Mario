#include "Block.h"

Block::Block(sf::Texture& texture) : Entity()
{

	sf::Vector2u boxSize = texture.getSize();
	boundary.setOrigin(sf::Vector2f(boxSize.x / 2.f, boxSize.y / 2.f)); 
	
	boundary.setSize(sf::Vector2f(boxSize.x, boxSize.y)); 
	boundary.setTexture(&texture); 
#ifdef _DEBUG
	boundary.setOutlineColor(sf::Color::Red);
	boundary.setOutlineThickness(-2);
#endif // _DEBUG
}

void Block::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(boundary, states); 
}

unsigned Block::getCategory() const
{
	return Category::Block;
}

sf::FloatRect Block::getBoundingRect() const
{
	return getWorldTransform().transformRect(boundary.getGlobalBounds()); 
}


