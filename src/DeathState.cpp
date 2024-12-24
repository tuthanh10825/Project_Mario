#include "DeathState.h"
#include <iostream>
DeathState::DeathState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0) {
    sf::RenderWindow& window = *getContext().window;

    sf::Vector2f windowPos = window.getView().getCenter();
    sf::Vector2f windowSize = window.getView().getSize();
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(windowPos + windowSize / 2.f);

    sf::Text retryOption;
    sf::Text exitOption;

    // Retry Option
    retryOption.setFont(context.fonts->get(Fonts::PixeloidMono));
    retryOption.setString("Retry");
    retryOption.setFillColor(sf::Color::White);
    sf::FloatRect bound = retryOption.getLocalBounds();
    retryOption.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2));
    retryOption.setPosition(windowPos);
    options.push_back(retryOption);

    // Exit Option
    exitOption.setFont(context.fonts->get(Fonts::PixeloidMono));
    exitOption.setString("Exit");
    exitOption.setFillColor(sf::Color::White);

    sf::FloatRect bound2 = exitOption.getLocalBounds();
    exitOption.setOrigin((bound2.left + bound2.width / 2.f), (bound2.top + bound2.height / 2.f));
    exitOption.setPosition(retryOption.getPosition() + sf::Vector2f(0.f, 100.f));
    options.push_back(exitOption);

    
}

void DeathState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(backgroundShape);

    for (sf::Text& text : options) {
        window.draw(text);
    }
}

bool DeathState::update(sf::Time dt) {
    return false;
}

bool DeathState::handleEvent(const sf::Event& event) {
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
        if (optionIndex == Retry) {
            
           requestStateClear();
           requestStackPushGame(World::Snapshot(lastChar, lastLevel)); 
            
        }
        if (optionIndex == Exit) {
            
            requestStateClear();
            requestStackPush(States::Menu);
            requestStackPush(States::LevelSelect); 
        }
    }
    return false;
}

void DeathState::applySnapshot(World::Snapshot snapshot)
{
    lastLevel = snapshot.getLevel(); 
    lastChar = snapshot.getCharacterType(); 
}


void DeathState::updateOptionText() {
    if (options.empty()) return;

    for (sf::Text& text : options) {
        text.setFillColor(sf::Color::White);
    }
    options[optionIndex].setFillColor(sf::Color::Red); // Highlight the selected option
}
