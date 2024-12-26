#pragma once
#include "SceneNode.h"
class Entity :public SceneNode{
public: 
	void setVelocity(sf::Vector2f velocity); 
	void setVelocity(float vx, float vy); 
	void setAcceleration(sf::Vector2f aceel); 
	void setAcceleration(float ax, float ay); 

	sf::Vector2f getVelocity() const;
	sf::Vector2f getAcceleration() const; 
	virtual sf::FloatRect getBoundingRect() const; 
	int getHp() const;
	void heal(int hp);
	void damage(int hp);
	void destroy();
	virtual void remove();
	virtual bool isDestroyed() const;
	Entity(int hp);

	virtual bool isAir() const; 
	virtual void setAir(bool isAir); 

	bool getFreeze() const;
	void setFreeze(bool freeze);

private: 
	const sf::Vector2f g = sf::Vector2f(0, 9.8); 
	sf::Vector2f velocity; 
	sf::Vector2f acceleration; 
	int hp;
	bool air; 
	bool freeze;
protected: 
	virtual void updateCurrent(sf::Time dt); 
	
};