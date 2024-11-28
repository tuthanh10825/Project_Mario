#pragma once
#include "StateStack.h"
class PauseState : public State {
private:
	enum OptionNames {
		Continue, 
		Exit, 
	};
	sf::RectangleShape backgroundShape;
	std::vector<sf::Text> options; 
	std::size_t optionIndex; 
public:
	PauseState(StateStack& stateStack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
private: 
	void updateOptionText();
};