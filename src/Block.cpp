#include "Block.h"

Block::Block(sf::Texture& texture) : Entity(1)
{

	sf::Vector2u boxSize = texture.getSize();
	//boundary.setOrigin(sf::Vector2f(boxSize.x / 2.f, boxSize.y / 2.f)); 
	
	boundary.setSize(sf::Vector2f(boxSize.x, boxSize.y)); 
	boundary.setTexture(&texture); 
	boundary.setOrigin(sf::Vector2f(boxSize.x / 2.f, boxSize.y / 2.f));
#ifdef _DEBUG
	boundary.setOutlineColor(sf::Color::Red);
	boundary.setOutlineThickness(-1);
#endif // _DEBUG
}
Block::Block(sf::Texture& texture, const sf::IntRect& intrect) : Entity(1) {
	boundary.setTexture(&texture); 
	boundary.setSize(sf::Vector2f(intrect.getSize().x, intrect.getSize().y));
	boundary.setTextureRect(intrect);
	boundary.setOrigin(sf::Vector2f(intrect.getSize().x / 2.f, intrect.getSize().y / 2.f));
#ifdef _DEBUG
	boundary.setOutlineColor(sf::Color::Red);
	boundary.setOutlineThickness(-1);
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


