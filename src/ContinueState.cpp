#include "ContinueState.h"

ContinueState::ContinueState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0)
{
	getContext().textures->load(Textures::SaveGameBackground, "textures/SaveGameMenu.png"); 
	background.setTexture(getContext().textures->get(Textures::SaveGameBackground)); 
	getContext().fonts->load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf"); 

	for (int i = 0; i < 5; ++i) {
		sf::Text option; 
		option.setFont(getContext().fonts->get(Fonts::PixeloidMono)); 
		option.setString(std::to_string(i)); 
		option.setCharacterSize(50); 
		option.setOrigin(option.getLocalBounds().getSize() / 2.f); 
		option.setPosition(500, 200 + 93 * i); 
		options.push_back(std::move(option)); 
	}
	for (int i = 0; i < getContext().caretaker->size(); ++i) {
		World::Snapshot snapshot = getContext().caretaker->getSnapshot(i); 
		std::string optionString = "Level: " + std::to_string(snapshot.getLevel()) + ", " + "Character: " + std::to_string(snapshot.getCharacterType()); 
		options[i].setString(optionString); 
		options[i].setCharacterSize(36); 
		options[i].setOrigin(options[i].getLocalBounds().getSize() / 2.f);
		options[i].setPosition(500, 200 + 93 * i); 
	}
	sf::Text back;
	back.setFont(getContext().fonts->get(Fonts::PixeloidMono));
	back.setCharacterSize(60);
	
	back.setString("Back");
	back.setOrigin(back.getLocalBounds().getSize() / 2.f);
	back.setPosition(500, 700);
	options.push_back(std::move(back));

	updateOptionText(); 
}

void ContinueState::draw()
{
	sf::RenderWindow& window = *getContext().window; 
	window.draw(background); 
	for (auto& text : options)
		window.draw(text); 
}

bool ContinueState::handleEvent(const sf::Event& event)
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
		if (optionIndex == options.size() - 1) {
			requestStackPop(); 
		}
		else {
			if (optionIndex < getContext().caretaker->size())
				requestStackPushGame(getContext().caretaker->getSnapshot(optionIndex)); 
		}
	}
	return false;
}

bool ContinueState::update(sf::Time dt)
{
	return false;
}

void ContinueState::updateOptionText()
{
	for (auto& option : options) {
		option.setColor(sf::Color::White); 
	}
	options[optionIndex].setColor(sf::Color::Yellow); 
}
