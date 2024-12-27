#include "MenuState.h"

MenuState::MenuState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0) {
	getContext().textures->load(Textures::TitleBackground, "textures/TitleBackground.png");
	getContext().textures->load(Textures::PlayButton, "textures/PlayButtons.png");
	getContext().textures->load(Textures::ExitButton, "textures/ExitButtons.png");
	getContext().textures->load(Textures::Title, "textures/Title.png");
	getContext().textures->load(Textures::Arrow, "textures/Arrow.png");
	getContext().textures->load(Textures::ContinueButton, "textures/ContinueButtons.png"); 

	mButtonSize = sf::Vector2i(240, 80);

	sf::RenderWindow& currWindow = *(context.window); 
	currWindow.setView(currWindow.getDefaultView()); 
	backgroundSprite.setTexture(getContext().textures->get(Textures::TitleBackground));
	sf::Sprite playOption; 
	playOption.setTexture(getContext().textures->get(Textures::PlayButton));
	playOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));
	
	
	sf::Vector2f windowSize = context.window->getView().getSize(); 
	sf::FloatRect bound = playOption.getLocalBounds(); 
	playOption.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2)); 
	playOption.setPosition(windowSize / 2.f); 
	options.push_back(playOption); 
	

	sf::Sprite continueOption;

	continueOption.setTexture(getContext().textures->get(Textures::ContinueButton));
	continueOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::FloatRect bound2 = continueOption.getLocalBounds(); 
	continueOption.setOrigin((bound2.left + bound2.width / 2.f),(bound2.top + bound2.height / 2.f)); 
	continueOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 100.f));
	options.push_back(continueOption);

	sf::Sprite exitOption;

	exitOption.setTexture(getContext().textures->get(Textures::ExitButton));
	exitOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::FloatRect bound3 = exitOption.getLocalBounds();
	exitOption.setOrigin((bound3.left + bound2.width / 2.f), (bound3.top + bound2.height / 2.f));
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 200.f));
	options.push_back(exitOption);

	title.setTexture(getContext().textures->get(Textures::Title));
	sf::FloatRect bound4 = title.getLocalBounds(); 
	title.setOrigin(bound4.left + bound4.width / 2.f, bound4.top + bound4.height / 2.f); 
	title.setPosition(sf::Vector2f(windowSize.x/2.f, windowSize.y/4.f));

	mArrow.setTexture(getContext().textures->get(Textures::Arrow));
	mArrow.setOrigin(mArrow.getLocalBounds().width, mArrow.getLocalBounds().height / 2.f);
	mArrow.setPosition(options[optionIndex].getPosition() - sf::Vector2f(120.f, 10.f));


	updateOptionText();
	
}
 
void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window; 
	//window.draw(backgroundSprite); 

	window.draw(backgroundSprite); 
	window.draw(title); 
	for (sf::Sprite& sprite : options) {
		window.draw(sprite); 
	}

	window.draw(mArrow);
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
		getContext().sounds->play(SoundEffect::ChangeOption);
		updateOptionText(); 
	}
	else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
		if (optionIndex < options.size() - 1) ++optionIndex;
		else optionIndex = 0; 
		getContext().sounds->play(SoundEffect::ChangeOption);
		updateOptionText(); 
	}
	if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Return) {
		if (optionIndex == Play) {
			requestStackPop(); 
			requestStackPush(States::LevelSelect);
		}
		if (optionIndex == Continue) { 
			requestStackPop(); 
			requestStackPush(States::Continue); 
		}
		if (optionIndex == Exit)
			requestStateClear(); 
	}
	return true;
}

void MenuState::updateOptionText()
{
	if (options.empty()) return;

	// Reset texture rects for all options
	for (sf::Sprite& sprite : options) {
		sprite.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));
	}

	// Highlight the selected option
	sf::IntRect textureRect = options[optionIndex].getTextureRect();
	textureRect.top += textureRect.height;
	options[optionIndex].setTextureRect(textureRect);

	// Update the arrow position to point at the selected option
	mArrow.setPosition(options[optionIndex].getPosition() - sf::Vector2f(120.f, 10.f));
}
