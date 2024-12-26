#include "State.h"

class ContinueState : public State {
public: 
	ContinueState(StateStack& stateStack, Context context); 
	void draw(); 
	bool handleEvent(const sf::Event& event); 
	bool update(sf::Time dt); 
private: 
	std::vector<sf::Text> options; 
	sf::Sprite background; 
	void updateOptionText(); 

	std::size_t optionIndex; 
};