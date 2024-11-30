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

	virtual sf::FloatRect getBoundingRect() const; 
	virtual void updateCurrent(sf::Time dt); 
	void setMoveLeft(bool isMove); 
	void setMoveRight(bool isMove); 
	void setAir(bool isAir); 
	bool isAir() const; 
private: 
	bool moveLeft; 
	bool moveRight; 
	bool air; 
	Type type; 
	sf::Sprite sprite; 

};