#include "MenuState.h"

MenuState::MenuState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0)
{
	sf::Text playOption; 

	sf::Vector2f windowSize = context.window->getView().getSize(); 
	playOption.setFont(context.fonts->get(Fonts::PixeloidMono)); 
	playOption.setString("Play"); 
	playOption.setColor(sf::Color::White);
	sf::FloatRect bound = playOption.getLocalBounds(); 
	playOption.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2)); 
	playOption.setPosition(windowSize / 2.f); 
	options.push_back(playOption); 
	

	sf::Text exitOption;

	exitOption.setFont(context.fonts->get(Fonts::PixeloidMono));
	exitOption.setString("Exit");
	exitOption.setColor(sf::Color::White); 

	sf::FloatRect bound2 = exitOption.getLocalBounds(); 
	exitOption.setOrigin((bound2.left + bound2.width / 2.f),(bound2.top + bound2.height / 2.f)); 
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 100.f));
	options.push_back(exitOption);


	title.setFont(context.fonts->get(Fonts::PixeloidSansBold)); 
	title.setString("Super Mario"); 

	title.setColor(sf::Color::White); 
	title.setCharacterSize(100); 
	sf::FloatRect bound3 = title.getLocalBounds(); 
	title.setOrigin(bound3.left + bound3.width / 2.f, bound3.top + bound3.height / 2.f); 
	title.setPosition(sf::Vector2f(windowSize.x/2.f, windowSize.y/3.f));

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
