#include "SettingState.h"
#include <iostream>
SettingState::SettingState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0) {
    sf::RenderWindow& window = *getContext().window;

    sf::Vector2f windowPos = window.getView().getCenter();
    sf::Vector2f windowSize = window.getView().getSize();
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(windowPos + windowSize / 2.f);

    sf::Text retryOption;
    sf::Text exitOption;

    // Retry Option
    retryOption.setFont(context.fonts->get(Fonts::PixeloidMono));
    retryOption.setString("Sound: ");
    retryOption.setFillColor(sf::Color::White);
    sf::FloatRect bound = retryOption.getLocalBounds();
    retryOption.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2));
    retryOption.setPosition(windowPos);
    options.push_back(retryOption);

    // Exit Option
    exitOption.setFont(context.fonts->get(Fonts::PixeloidMono));
    exitOption.setString("Music: ");
    exitOption.setFillColor(sf::Color::White);

    sf::FloatRect bound2 = exitOption.getLocalBounds();
    exitOption.setOrigin((bound2.left + bound2.width / 2.f), (bound2.top + bound2.height / 2.f));
    exitOption.setPosition(retryOption.getPosition() + sf::Vector2f(0.f, 100.f));
    options.push_back(exitOption);

    // Retry Option
    exitOption.setFont(context.fonts->get(Fonts::PixeloidMono));
    exitOption.setString("Back");
    exitOption.setFillColor(sf::Color::White);
    sf::FloatRect bound3 = exitOption.getLocalBounds();
    exitOption.setOrigin((bound3.left + bound3.width / 2.f), (bound3.top + bound3.height / 2));
    exitOption.setPosition(retryOption.getPosition() + sf::Vector2f(0.f, 200.f));
    options.push_back(exitOption);

    updateOptionText();
}

void SettingState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(backgroundShape);

    for (sf::Text& text : options) {
        window.draw(text);
    }
}

bool SettingState::update(sf::Time dt) {
    return false;
}

bool SettingState::handleEvent(const sf::Event& event) {
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
        if (optionIndex == Sound) {
			getContext().sounds->setVolume(100 - getContext().sounds -> getVolume());
            updateOptionText();
        }
        if (optionIndex == Music) {
			getContext().musics ->setVolume(100 - getContext().musics->getVolume());
            updateOptionText();
        }
		if (optionIndex == Exit)
			requestStackPop();
    }
    return false;
}

void SettingState::applySnapshot(World::Snapshot snapshot)
{
    lastLevel = snapshot.getLevel();
    lastChar = snapshot.getCharacterType();
}


void SettingState::updateOptionText() {
    if (options.empty()) return;
	if (getContext().musics->getVolume() == 0) {
		options[Music].setString("Music: Off");
	}
	else {
		options[Music].setString("Music: On");
	}
	if (getContext().sounds->getVolume() == 0) {
		options[Sound].setString("Sound: Off");
	}
	else {
		options[Sound].setString("Sound: On");
	}
    for (sf::Text& text : options) {

        text.setFillColor(sf::Color::White);
    }
    options[optionIndex].setFillColor(sf::Color::Red); // Highlight the selected option
}
