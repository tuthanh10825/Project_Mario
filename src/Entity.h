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
	bool isDestroyed() const;
	Entity(int hp);
private: 
	const sf::Vector2f g = sf::Vector2f(0, 9.8); 
	sf::Vector2f velocity; 
	sf::Vector2f acceleration; 
	int hp;
protected: 
	virtual void updateCurrent(sf::Time dt); 
	
};