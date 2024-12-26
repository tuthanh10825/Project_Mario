#pragma once
#include "State.h"

class MenuState : public State {
private: 
	enum OptionNames {
		Play, 
		Continue, 
		Exit
	};
	std::vector<sf::Sprite> options; 
	std::size_t optionIndex; 
	sf::Sprite backgroundSprite; 
	sf::Sprite title; 
	sf::Vector2i mButtonSize;
	sf::Sprite mArrow;

public: 
	MenuState(StateStack&, Context context); 
	virtual void draw(); 
	virtual bool update(sf::Time dt); 
	virtual bool handleEvent(const sf::Event& event); 

	void updateOptionText();
};