#pragma once
#include "SceneNode.h"
class Entity :public SceneNode{
public: 
	void setVelocity(sf::Vector2f velocity); 
	void setVelocity(float vx, float vy); 
	sf::Vector2f getVelocity() const;
	virtual sf::FloatRect getBoundingRect() const = 0; 

	Entity(bool gApplied = false, float g = 20.f);
private: 
	sf::Vector2f velocity; 
	virtual void updateCurrent(sf::Time dt); 
	
	float g; 
	bool gApplied; 

};