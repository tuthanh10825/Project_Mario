#include "Player.h"

Player::Player(Type type, const TextureHolder& textures) : type(type), textureHolder(textures)
{
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states); 
}
