#include "SpriteNode.h"
#include <cassert>
SpriteNode::SpriteNode(const sf::Texture& texture) :
	sprite(texture) 
{
}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) : 
	sprite(texture, rect)
{
	/*assert(texture.isRepeated()); 
	float scale = 1.f * rect.height / texture.getSize().y;
	sprite.setScale(scale, scale); */
	//sprite.setTextureRect(rect); 
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states); 
}
