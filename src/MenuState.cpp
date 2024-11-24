#include "MenuState.h"

MenuState::MenuState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0)
{
	sf::Text playOption; 

	sf::Vector2f windowSize = context.window->getView().getSize(); 
	playOption.setFont(context.fonts->get(Fonts::PixeloidMono)); 
	playOption.setString("Play"); 
	playOption.setColor(sf::Color::White);

	playOption.setPosition(windowSize / 2.f); 
	options.push_back(playOption); 
	

	sf::Text exitOption;

	exitOption.setFont(context.fonts->get(Fonts::PixeloidMono));
	exitOption.setString("Exit");
	exitOption.setColor(sf::Color::White); 

	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 100.f));
	options.push_back(exitOption);


	title.setFont(context.fonts->get(Fonts::PixeloidSansBold)); 
	title.setString("Super Mario"); 

	title.setColor(sf::Color::White); 
	title.setCharacterSize(100); 
	title.setPosition(windowSize/3.f);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window; 
	//window.draw(backgroundSprite); 


	window.draw(title); 
	for (sf::Text& text : options) {
		window.draw(text); 
	}
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
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
	if (event.key.code == sf::Keyboard::Return) {
		if (optionIndex == Exit)
			requestStateClear(); 
	}
	return true;
}

void MenuState::updateOptionText()
{
	if (options.empty()) return; 

	for (sf::Text& text : options) {
		text.setColor(sf::Color::White); 
	}
	options[optionIndex].setColor(sf::Color::Red); 

}
