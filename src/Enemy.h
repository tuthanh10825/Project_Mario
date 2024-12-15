#pragma once
#include "Entity.h";
#include "ResourceHolder.h";
#include "Animation.h";

class Enemy : public Entity {
public:
	enum Type {
		Goomba,
		Koopa,
		Plant,
	};
	enum State
	{
		alive = 0,
		movRight = 1,
		movLeft = 2,
		die = 3
	};
	explicit Enemy(Type type, TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;
	virtual void updateCurrent(sf::Time dt);

	void setMoveLeft(bool isMove);
	void setMoveRight(bool isMove);

	bool isMoveLeft() const;
	bool isMoveRight() const;

	void remove();
	bool isMarkedForRemoval() const;
private:

	bool moveLeft;
	bool moveRight;
	bool air;
	Type type;
	sf::RectangleShape sprite;
	bool showDead;
	Animation mDead;
	Animation mMovRight;
	Animation mMovLeft;
};
