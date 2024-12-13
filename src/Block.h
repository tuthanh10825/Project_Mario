#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "ID.h"

class Block : public Entity{
public: 
	explicit Block(sf::Texture &texture); 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned getCategory() const; 

	virtual sf::FloatRect getBoundingRect() const; 
private: 
	sf::RectangleShape boundary; 
protected: 
	virtual void updateCurrent(sf::Time dt) {};
};