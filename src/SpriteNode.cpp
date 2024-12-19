#include "SpriteNode.h"
SpriteNode::SpriteNode(const sf::Texture& texture) :
	sprite(texture) 
{
}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) : 
	sprite(texture)
{
	float scale = 1.f * rect.height / texture.getSize().y;
	sprite.setScale(scale, scale); 
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states); 
}
