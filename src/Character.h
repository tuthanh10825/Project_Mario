#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "Animation.h"

class Character : public Entity {
public: 
	enum Type {
		Character1,
		Character2,
	};
	explicit Character(Type type, TextureHolder& textures); 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
	virtual unsigned getCategory() const; 

	virtual sf::FloatRect getBoundingRect() const; 
	virtual void updateCurrent(sf::Time dt); 

	void setMoveLeft(bool isMove); 
	void setMoveRight(bool isMove); 
	void setJump(bool isJump); 
	
	bool isMoveLeft() const; 
	bool isMoveRight() const; 
	bool isJump() const; 

	void setAir(bool isAir);
	bool isAir() const;
private: 

	bool moveLeft; 
	bool moveRight; 
	bool air; 
	bool jump; 
	Type type; 
	sf::RectangleShape sprite; 
	Animation mMovRight;
	Animation mMovLeft;

};