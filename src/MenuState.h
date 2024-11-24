#include "State.h"

class MenuState : public State {
private: 
	enum OptionNames {
		Play, 
		Exit
	};
	std::vector<sf::Text> options; 
	std::size_t optionIndex; 
	sf::Sprite backgroundSprite; 
	sf::Text title; 

public: 
	MenuState(StateStack&, Context context); 
	virtual void draw(); 
	virtual bool update(sf::Time dt); 
	virtual bool handleEvent(const sf::Event& event); 

	void updateOptionText();
};