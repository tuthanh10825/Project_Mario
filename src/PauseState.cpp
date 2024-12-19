#include "PauseState.h"

PauseState::PauseState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0) {
	sf::RenderWindow& window = *getContext().window; 
	getContext().textures->load(Textures::ExitButton, "textures/ExitButtons.png");
	getContext().textures->load(Textures::ContinueButton, "textures/ContinueButtons.png");

	mButtonSize = sf::Vector2i(240, 80);

	sf::Vector2f windowPos = window.getView().getCenter();
	sf::Vector2f windowSize = window.getView().getSize(); 
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(windowPos + windowSize / 2.f);

	sf::Sprite exitOption;

	exitOption.setTexture(getContext().textures->get(Textures::ExitButton));
	exitOption.setTextureRect(sf::IntRect(0, 0, 160, 80));

	sf::Sprite continueOption;
	
	continueOption.setTexture(getContext().textures->get(Textures::ContinueButton));
	continueOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));

	sf::FloatRect bound = continueOption.getLocalBounds();
	continueOption.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2));
	continueOption.setPosition(windowPos);
	options.push_back(continueOption);

	sf::FloatRect bound2 = exitOption.getLocalBounds();
	exitOption.setOrigin((bound2.left + bound2.width / 2.f), (bound2.top + bound2.height / 2.f));
	exitOption.setPosition(continueOption.getPosition() + sf::Vector2f(0.f, 100.f));
	options.push_back(exitOption);

	// Highlight the selected option
	sf::IntRect textureRect = options[optionIndex].getTextureRect();
	textureRect.top += textureRect.height;
	options[optionIndex].setTextureRect(textureRect);

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundShape);

	for (sf::Sprite& text : options) {
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
		getContext().sounds->play(SoundEffect::ChangeOption);
		updateOptionText();
	}
	else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
		if (optionIndex < options.size() - 1) ++optionIndex;
		else optionIndex = 0;
		getContext().sounds->play(SoundEffect::ChangeOption);
		updateOptionText();
	}
	else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Return) {
		if (optionIndex == Continue) {
			requestStackPop();
		}
		if (optionIndex == Exit) {
			requestStateClear();
			requestStackPush(States::LevelSelect);
		}

	}
	return false;
}

void PauseState::updateOptionText() {
	if (options.empty()) return;

	// Reset texture rects for all options
	for (sf::Sprite& sprite : options) {
		sprite.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));
	}
	// Highlight the selected option
	sf::IntRect textureRect = options[optionIndex].getTextureRect();
	textureRect.top += textureRect.height;
	options[optionIndex].setTextureRect(textureRect);
}
