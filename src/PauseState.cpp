#include "PauseState.h"

PauseState::PauseState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0) {
	sf::RenderWindow& window = *getContext().window; 


	sf::Vector2f windowPos = window.getView().getCenter();
	sf::Vector2f windowSize = window.getView().getSize(); 
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(windowPos + windowSize / 2.f);

	sf::Text continueOption; 
	sf::Text exitOption;
	
	continueOption.setFont(context.fonts->get(Fonts::PixeloidMono));
	continueOption.setString("Continue");
	continueOption.setColor(sf::Color::White);
	sf::FloatRect bound = continueOption.getLocalBounds();
	continueOption.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2));
	continueOption.setPosition(windowPos);
	options.push_back(continueOption);

	exitOption.setFont(context.fonts->get(Fonts::PixeloidMono));
	exitOption.setString("Exit");
	exitOption.setColor(sf::Color::White);

	sf::FloatRect bound2 = exitOption.getLocalBounds();
	exitOption.setOrigin((bound2.left + bound2.width / 2.f), (bound2.top + bound2.height / 2.f));
	exitOption.setPosition(continueOption.getPosition() + sf::Vector2f(0.f, 100.f));
	options.push_back(exitOption);

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundShape);

	for (sf::Text& text : options) {
		window.draw(text);
	}
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
		if (optionIndex) --optionIndex;
		else optionIndex = options.size() - 1;

		updateOptionText();
	}
	else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
		if (optionIndex < options.size() - 1) ++optionIndex;
		else optionIndex = 0;
		updateOptionText();
	}
	else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Return) {
		if (optionIndex == Continue) {
			requestStackPop();
		}
		if (optionIndex == Exit) {
			requestStateClear();
			requestStackPush(States::Menu);
		}

	}
	return false;
}

void PauseState::updateOptionText() {
	if (options.empty()) return;

	for (sf::Text& text : options) {
		text.setColor(sf::Color::White);
	}
	options[optionIndex].setColor(sf::Color::Red);
}
