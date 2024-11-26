#pragma once
#include "Entity.h"
#include "ResourceHolder.h"

class Player : public Entity {
public: 
	enum Type {
		Character1,
	};
	explicit Player(Type type, const TextureHolder& textures); 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 

private: 
	Type type; 
	sf::Sprite sprite; 

};