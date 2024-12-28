#pragma once
#include <sfml/Graphics.hpp>
#include "ResourceHolder.h"
class Hub {
private: 

	sf::RenderWindow& window; 
	FontHolder& fonts; 
	TextureHolder& textures; 
	
	sf::Sprite woodenBox;

	sf::Text hpText; 
	sf::Text hpCount; 
	sf::Sprite heart;

	sf::Text timeText; 
	sf::Text timeCount; 

	sf::Text pointText; 
	sf::Text pointCount; 
	

public: 
	Hub(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts); 

	void setHP(int hp); 
	void setTime(float time); 
	void setPoint(int point); 

	void updateView(const sf::View& worldView); 
	void draw();

};