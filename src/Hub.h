#pragma once
#include <sfml/Graphics.hpp>
#include "State.h"
class Hub {
private: 
	State::Context context; 

	sf::Text hpText; 
	sf::Text hpCount; 
	sf::Sprite heart;

	sf::Text timeText; 
	sf::Text timeCount; 

	sf::Text pointText; 
	sf::Text pointCount; 
	

public: 
	Hub(State::Context context); 

	void setHP(int hp); 
	void setTime(float time); 
	void setPoint(int point); 

	void updateView(const sf::View& worldView); 
	void draw();

};