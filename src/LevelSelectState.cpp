#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(StateStack& stateStack, Context context) : State(stateStack, context), optionIndex(0) {
	getContext().textures->load(Textures::TitleBackground, "textures/TitleBackground.png");
	getContext().textures->load(Textures::Level1, "textures/Level1.png");
	getContext().textures->load(Textures::Level2, "textures/Level2.png");
	getContext().textures->load(Textures::Level3, "textures/Level3.png");
	getContext().textures->load(Textures::Back, "textures/Back.png");
	getContext().textures->load(Textures::Arrow, "textures/Arrow.png");

	mButtonSize = sf::Vector2i(320, 160);

	sf::RenderWindow& currWindow = *(context.window);
	currWindow.setView(currWindow.getDefaultView());
	backgroundSprite.setTexture(getContext().textures->get(Textures::TitleBackground));

	//__LEVEL 1
	sf::Sprite level1Option;
	level1Option.setTexture(getContext().textures->get(Textures::Level1));
	level1Option.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::Vector2f windowSize = context.window->getView().getSize();
	sf::FloatRect bound = level1Option.getLocalBounds();
	level1Option.setOrigin((bound.left + bound.width / 2.f), (bound.top + bound.height / 2));
	level1Option.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 4.f));
	options.push_back(level1Option);

	//__LEVEL 2
	sf::Sprite level2Option;
	level2Option.setTexture(getContext().textures->get(Textures::Level2));
	level2Option.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::FloatRect bound2 = level2Option.getLocalBounds();
	level2Option.setOrigin((bound2.left + bound2.width / 2.f), (bound2.top + bound2.height / 2));
	level2Option.setPosition(level1Option.getPosition() + sf::Vector2f(0.f, 120.f));
	options.push_back(level2Option);

	//__LEVEL 3
	sf::Sprite level3Option;
	level3Option.setTexture(getContext().textures->get(Textures::Level3));
	level3Option.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));

	sf::FloatRect bound3 = level3Option.getLocalBounds();
	level3Option.setOrigin((bound3.left + bound3.width / 2.f), (bound3.top + bound3.height / 2));
	level3Option.setPosition(level2Option.getPosition() + sf::Vector2f(0.f, 120.f));
	options.push_back(level3Option);

	
	//__BACK
	sf::Sprite backOption;
	backOption.setTexture(getContext().textures->get(Textures::Back));
	backOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::FloatRect bound4 = backOption.getLocalBounds();
	backOption.setOrigin((bound4.left + bound4.width / 2.f), (bound4.top + bound4.height / 2));
	backOption.setPosition(level3Option.getPosition() + sf::Vector2f(0.f, 150.f));
	options.push_back(backOption);


	//__ARROW
	mArrow.setTexture(getContext().textures->get(Textures::Arrow));
	mArrow.setOrigin(mArrow.getLocalBounds().width, mArrow.getLocalBounds().height / 2.f);
	mArrow.setPosition(options[optionIndex].getPosition() - sf::Vector2f(150.f, 10.f));

	updateOption();
}

void LevelSelectState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	//window.draw(backgroundSprite); 

	window.draw(backgroundSprite);
	
	for (sf::Sprite& sprite : options) {
		window.draw(sprite);
	}

	window.draw(mArrow);
}

bool LevelSelectState::update(sf::Time dt)
{
	return true;
}

bool LevelSelectState::handleEvent(const sf::Event& event)
{
	if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
		if (optionIndex) --optionIndex;
		else optionIndex = options.size() - 1;

		updateOption();
	}
	else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
		if (optionIndex < options.size() - 1) ++optionIndex;
		else optionIndex = 0;
		updateOption();
	}
	if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Return) {
		if (optionIndex == Level1) {
			requestStackPop();
			requestStackPushGame(Level::Easy);
		}
		if (optionIndex == Level2) {

		}
		if (optionIndex == Level3) {

		}
		if (optionIndex == Back) {
			requestStateClear();
			requestStackPush(States::Menu);
		}
			
	}
	return true;
}

void LevelSelectState::updateOption()
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
	mArrow.setPosition(options[optionIndex].getPosition() - sf::Vector2f(150.f, 10.f));
}