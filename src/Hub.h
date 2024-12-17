#pragma once
#include <sfml/Graphics.hpp>
#include "State.h"
class Hub {
private: 
	State::Context context; 
	sf::Font font;
	sf::Text hpText; 
	sf::Text timeText; 
	sf::Text timeCount; 

	sf::Text pointText; 
	sf::Text pointCount; 
	sf::Sprite heart; 

	int hp;
	float time; 
	int point; 
public: 
	Hub(State::Context context); 
	void setHP(int hp); 

	void update(sf::Time dt); 
	void draw();
};