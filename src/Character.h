#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "Animation.h"
#include "Projectile.h"

class Character : public Entity {
public: 
	enum Type {
		Character1,
		Character2,
	};
	enum State {
		alive = 0,
		movRight = 1,
		movLeft = 2,
		die = 3
	};

	explicit Character(Type type, TextureHolder& textures); 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
	virtual unsigned getCategory() const; 

	virtual sf::FloatRect getBoundingRect() const; 
	virtual void updateCurrent(sf::Time dt); 

	void setMoveLeft(bool isMove); 
	void setMoveRight(bool isMove); 
	void setJump(bool isJump);

	void incrJump(); 
	short countJump(); 
	void resetJump(); 

	bool isMoveLeft() const; 
	bool isMoveRight() const; 
	bool isJump() const; 

	void createProjectile(SceneNode& node, TextureHolder& textures, sf::Vector2f pos, Projectile::Type type);
	
	void setFire(bool fire);
	bool isFire() const;
	bool canFire() const;

	void incrPoint(int point);
	int getPoint() const;

	bool hasFire() const;
	void setHasFireFlower(bool hasFireFlower);

	Command getFireCommand();
private: 

	bool moveLeft; 
	bool moveRight; 
	bool jump; 
	short jumpCount; 
	int point;
	bool hasFireFlower;

	Type type; 
	sf::RectangleShape sprite; 
	Animation mMovRight;
	Animation mMovLeft;
	bool fire;
	sf::Time mFireCountdown;
	Command mFireCommand;
};