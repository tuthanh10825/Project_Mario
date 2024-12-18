#pragma once
#include "Entity.h"
#include "ID.h"
#include "ResourceHolder.h"

class Projectitle : public Entity {
public:
	enum Type {
		CharBullet,
		EnemyBullet,
		TypeCount
	};
	Projectitle(Type type, TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;
	virtual void updateCurrent(sf::Time dt);

	int getDamage() const;
	void setDamage(int damage);

	void setTouchGround(bool isTouch);
private:
	sf::RectangleShape sprite;
	int damage;
	Type type;
	bool isTouchGround;
};