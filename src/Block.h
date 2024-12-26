#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "ID.h"

class Block : public Entity{
public: 
	explicit Block(sf::Texture &texture); 
	explicit Block(sf::Texture& texture, const sf::IntRect& rectangle); 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned getCategory() const; 

	virtual sf::FloatRect getBoundingRect() const; 
protected: 
	sf::RectangleShape boundary; 
	virtual void updateCurrent(sf::Time dt) {};
};