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

	void setAir(bool isAir);
	bool isAir() const;

	void setDead(bool isDead);
	bool isDead() const;
private:

	bool moveLeft;
	bool moveRight;
	bool air;
	bool dead;
	Type type;
	sf::RectangleShape sprite;
	sf::RectangleShape deadSprite;
	Animation mMovRight;
	Animation mMovLeft;
};
