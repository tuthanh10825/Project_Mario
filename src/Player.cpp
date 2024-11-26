#include "Player.h"

static Textures::ID toTextureID(Player::Type type) {
	switch (type) {
	case Player::Character1: 
		return Textures::Character1;
	}
}
Player::Player(Type type, const TextureHolder& textures) : type(type), sprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bound = sprite.getLocalBounds(); 
	sprite.setOrigin(bound.width / 2.f, bound.height / 2.f); 
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states); 
}
