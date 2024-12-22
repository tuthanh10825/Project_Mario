#include "PauseState.h"

PauseState::PauseState(StateStack& stateStack, Context context)
    : State(stateStack, context), optionIndex(0), volumeLevel(50.0f) {
    sf::RenderWindow& window = *getContext().window;

    // Load textures for buttons
    getContext().textures->load(Textures::ExitButton, "textures/ExitButtons.png");
    getContext().textures->load(Textures::ContinueButton, "textures/ContinueButtons.png");

    mButtonSize = sf::Vector2i(240, 80);

    sf::Vector2f windowPos = window.getView().getCenter();
    sf::Vector2f windowSize = window.getView().getSize();

    // Background overlay
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(windowPos + windowSize / 2.f);

    // Exit option
    sf::Sprite exitOption;
    exitOption.setTexture(getContext().textures->get(Textures::ExitButton));
    exitOption.setTextureRect(sf::IntRect(0, 0, 160, 80));

    // Continue option
    sf::Sprite continueOption;
    continueOption.setTexture(getContext().textures->get(Textures::ContinueButton));
    continueOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));

    // Center the buttons
    sf::FloatRect bound = continueOption.getLocalBounds();
    continueOption.setOrigin(bound.left + bound.width / 2.f, bound.top + bound.height / 2.f);
    continueOption.setPosition(windowPos);
    options.push_back(continueOption);

    sf::FloatRect bound2 = exitOption.getLocalBounds();
    exitOption.setOrigin(bound2.left + bound2.width / 2.f, bound2.top + bound2.height / 2.f);
    exitOption.setPosition(continueOption.getPosition() + sf::Vector2f(0.f, 100.f));
    options.push_back(exitOption);

    // Highlight the first option
    sf::IntRect textureRect = options[optionIndex].getTextureRect();
    textureRect.top += textureRect.height;
    options[optionIndex].setTextureRect(textureRect);

    // Slider bar
    sliderBar.setSize(sf::Vector2f(200.f, 10.f));
    sliderBar.setFillColor(sf::Color(100, 100, 100));
    sliderBar.setPosition(window.getView().getCenter() + sf::Vector2f(-100.f, 50.f));

    // Slider handle
    sliderHandle.setSize(sf::Vector2f(20.f, 20.f));
    sliderHandle.setFillColor(sf::Color(200, 200, 200));
    sliderHandle.setOrigin(sliderHandle.getSize() / 2.f);
    sliderHandle.setPosition(sliderBar.getPosition() + sf::Vector2f(sliderBar.getSize().x * (volumeLevel / 100.f), 0.f));
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;

    // Draw background
    window.draw(backgroundShape);

    // Draw options
    for (sf::Sprite& text : options) {
        window.draw(text);
    }

    // Draw slider
    window.draw(sliderBar);
    window.draw(sliderHandle);
}

bool PauseState::update(sf::Time dt) {
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (optionIndex > 0) --optionIndex;
            else optionIndex = VolumeSlider; 
            updateOptionText();
        }
        else if (event.key.code == sf::Keyboard::Down) {
            if (optionIndex < VolumeSlider) ++optionIndex;
            else optionIndex = 0;
            updateOptionText();
        }
        else if (optionIndex == VolumeSlider) {
            if (event.key.code == sf::Keyboard::Left) {
                decreaseVolume();
            }
            else if (event.key.code == sf::Keyboard::Right) {
                increaseVolume();
            }
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (optionIndex == Continue) {
                requestStackPop();
            }
            else if (optionIndex == Exit) {
                requestStateClear();
                requestStackPush(States::LevelSelect);
            }
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

    // Highlight the selected option if it's not the slider
    if (optionIndex != VolumeSlider) {
        sf::IntRect textureRect = options[optionIndex].getTextureRect();
        textureRect.top += textureRect.height;
        options[optionIndex].setTextureRect(textureRect);
    }
    else {
        updateSliderAppearance();
    }
}

void PauseState::updateSliderAppearance() {
    // Change slider handle color when selected
    sliderHandle.setFillColor(optionIndex == VolumeSlider ? sf::Color::Yellow : sf::Color(200, 200, 200));
}

void PauseState::decreaseVolume() {
    volumeLevel = std::max(0.0f, volumeLevel - 1.0f);
    sliderHandle.setPosition(sliderBar.getPosition() + sf::Vector2f(sliderBar.getSize().x * (volumeLevel / 100.f), 0.f));
    std::cout << volumeLevel << std::endl;
    getContext().musics->setVolume(volumeLevel); 
}

void PauseState::increaseVolume() {
    volumeLevel = std::min(100.0f, volumeLevel + 1.0f);
    sliderHandle.setPosition(sliderBar.getPosition() + sf::Vector2f(sliderBar.getSize().x * (volumeLevel / 100.f), 0.f));
    std::cout << volumeLevel << std::endl;
    getContext().musics->setVolume(volumeLevel);
}