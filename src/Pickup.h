#pragma once
#include "Entity.h"
#include "Character.h"
#include "ResourceHolder.h"
#include "Animation.h"

class Pickup : public Entity 
{
public: 
	enum Type 
	{
		Mushroom,
		Coin,
		FireFlower,
		TypeCount
	};
public:
	explicit Pickup(Type type, TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;
	virtual void updateCurrent(sf::Time dt);

	void setMoveRight(bool isMove);
	void setMoveLeft(bool isMove);

	virtual void apply(Character& character) const;
private:
	Type type;
	bool moveRight;
	bool moveLeft;
	sf::RectangleShape sprite;
};