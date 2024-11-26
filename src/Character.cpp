#include "Character.h"

static Textures::ID toTextureID(Character::Type type) {
	switch (type) {
	case Character::Character1: 
		return Textures::Character1;
	}
}
Character::Character(Type type, const TextureHolder& textures) : type(type), sprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bound = sprite.getLocalBounds(); 
	sprite.setOrigin(bound.width / 2.f, bound.height / 2.f); 
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states); 
}

unsigned Character::getCategory() const
{
	return Category::Player; 
}
