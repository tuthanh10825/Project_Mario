#pragma once
#include "Entity.h"
#include "ResourceHolder.h"

class Character : public Entity {
public: 
	enum Type {
		Character1,
	};
	explicit Character(Type type, const TextureHolder& textures); 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
	virtual unsigned getCategory() const; 

private: 
	Type type; 
	sf::Sprite sprite; 

};