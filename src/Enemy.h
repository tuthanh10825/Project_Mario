#pragma once
#include "Entity.h";
#include "ResourceHolder.h";
#include "Animation.h";

class Enemy : public Entity {
public:
	enum Type {
		Goomba,
		Plant,
		Bird,
		TypeCount
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

	void setPosition(sf::Vector2f pos);
	Enemy::Type getType();
private:

	bool moveLU;
	bool moveRD;

	Type type;
	sf::RectangleShape sprite;
	bool showDead;
	sf::Vector2f origin;
	Animation mDead;
	Animation mMovLU; 
	Animation mMovRD;
};
