#pragma once
#include "Entity.h"
#include "ID.h"
#include "ResourceHolder.h"
#include "Animation.h"

class Projectile : public Entity {
public:
	enum Type {
		CharBullet,
		EnemyBullet,
		TypeCount
	};
	Projectile(Type type, TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;
	virtual void updateCurrent(sf::Time dt);

	int getDamage() const;
	void setDamage(int damage);

private:
	sf::RectangleShape sprite;
	Animation animation;
	int damage;
	Type type;
};