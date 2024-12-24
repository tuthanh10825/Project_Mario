#include "WinState.h"

WinState::WinState(StateStack& stateStack, Context context) : State(stateStack, context), firstTime(true)
{
	getContext().textures->load(Textures::Win, "textures/SYouWIN.png"); 

	total.setTexture(getContext().textures->get(Textures::Win));
	total.setFrameSize(sf::Vector2i(1000, 800)); 
	total.setNumFrames(2); 
	total.setDuration(sf::seconds(0.5f));
	total.setRepeating(true); 
	total.setOrigin(500, 400);
	total.setPosition(getContext().window->getView().getCenter()); 
}
bool WinState::update(sf::Time dt) {
	total.update(dt);
	return false; 
}
void WinState::draw() {
	getContext().window->draw(total); 
}

bool WinState::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		requestStateClear(); 
		requestStackPush(States::Menu); 
		requestStackPush(States::LevelSelect); 
	}
	return false; 
}



