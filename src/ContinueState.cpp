#include "ContinueState.h"

ContinueState::ContinueState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0)
{
	getContext().textures->load(Textures::TitleBackground, "textures/TitleBackground.png"); 
	background.setTexture(getContext().textures->get(Textures::TitleBackground)); 
	getContext().fonts->load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf"); 

	for (int i = 0; i < 5; ++i) {
		sf::Text option; 
		option.setFont(getContext().fonts->get(Fonts::PixeloidMono)); 
		option.setCharacterSize(60); 
		std::string optionString = (std::to_string(i) + "i"); 
		option.setString(optionString); 
		option.setOrigin(option.getLocalBounds().getSize() / 2.f); 
		option.setPosition(500, 200 + 90 * i); 
		options.push_back(std::move(option)); 
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
			requestStackPush(States::Menu); 
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
	options[optionIndex].setColor(sf::Color::Red); 
}
