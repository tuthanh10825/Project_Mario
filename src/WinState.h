#include "State.h"
#include "Animation.h"

class WinState : public State {
public: 
	WinState(StateStack& stateStack, Context context); 
	void draw(); 
	bool handleEvent(const sf::Event& event);
	bool update(sf::Time dt); 

private: 
	Animation total; 
	bool firstTime; 
};