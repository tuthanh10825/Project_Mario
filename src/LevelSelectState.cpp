#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(StateStack& stateStack, Context context) : State(stateStack, context), levelOptionIndex(0), charOptionIndex(0), mIsLevelSelected(false)
{
	getContext().textures->load(Textures::TitleBackground, "textures/TitleBackground.png");
	getContext().textures->load(Textures::Level1, "textures/Level1.png");
	getContext().textures->load(Textures::Level2, "textures/Level2.png");
	getContext().textures->load(Textures::Level3, "textures/Level3.png");
	getContext().textures->load(Textures::Back, "textures/Back.png");
	getContext().textures->load(Textures::Char1Select, "textures/Char1.png");
	getContext().textures->load(Textures::Char2Select, "textures/Char2.png");

	mButtonSize = sf::Vector2i(320, 160);
	mCharSize = sf::Vector2i(120, 120);
	
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
	level1Option.setPosition(sf::Vector2f((windowSize.x / 8.f)*3.f - 100.f, windowSize.y / 4.f));
	levelOptions.push_back(level1Option);

	//__LEVEL 2
	sf::Sprite level2Option;
	level2Option.setTexture(getContext().textures->get(Textures::Level2));
	level2Option.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::FloatRect bound2 = level2Option.getLocalBounds();
	level2Option.setOrigin((bound2.left + bound2.width / 2.f), (bound2.top + bound2.height / 2));
	level2Option.setPosition(level1Option.getPosition() + sf::Vector2f(0.f, 120.f));
	levelOptions.push_back(level2Option);

	//__LEVEL 3
	sf::Sprite level3Option;
	level3Option.setTexture(getContext().textures->get(Textures::Level3));
	level3Option.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));

	sf::FloatRect bound3 = level3Option.getLocalBounds();
	level3Option.setOrigin((bound3.left + bound3.width / 2.f), (bound3.top + bound3.height / 2));
	level3Option.setPosition(level2Option.getPosition() + sf::Vector2f(0.f, 120.f));
	levelOptions.push_back(level3Option);

	
	//__BACK
	sf::Sprite backOption;
	backOption.setTexture(getContext().textures->get(Textures::Back));
	backOption.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));


	sf::FloatRect bound4 = backOption.getLocalBounds();
	backOption.setOrigin((bound4.left + bound4.width / 2.f), (bound4.top + bound4.height / 2));
	backOption.setPosition((windowSize.x / 2.f), (windowSize.y / 4.f) * 3.f);
	levelOptions.push_back(backOption);


	//__ARROW
	mArrow.setTexture(getContext().textures->get(Textures::Arrow));
	mArrow.setOrigin(mArrow.getLocalBounds().width, mArrow.getLocalBounds().height / 2.f);
	mArrow.setPosition(levelOptions[levelOptionIndex].getPosition() - sf::Vector2f(120.f, 10.f));

	//__CHARACTER 1
	sf::Sprite char1Option;
	char1Option.setTexture(getContext().textures->get(Textures::Char1Select));
	char1Option.setTextureRect(sf::IntRect(0, 0, mCharSize.x, mCharSize.y));

	sf::FloatRect bound5 = char1Option.getLocalBounds();
	char1Option.setOrigin((bound5.left + bound5.width / 2.f), (bound5.top + bound5.height / 2));
	char1Option.setPosition(sf::Vector2f((windowSize.x / 8.f) * 6.f, windowSize.y / 4.f));
	charOptions.push_back(char1Option);

	//__CHARACTER 2
	sf::Sprite char2Option;
	char2Option.setTexture(getContext().textures->get(Textures::Char2Select));
	char2Option.setTextureRect(sf::IntRect(0, 0, mCharSize.x, mCharSize.y));

	sf::FloatRect bound6 = char2Option.getLocalBounds();
	char2Option.setOrigin((bound6.left + bound6.width / 2.f), (bound6.top + bound6.height / 2));
	char2Option.setPosition(char1Option.getPosition() + sf::Vector2f(0.f, 250.f));
	charOptions.push_back(char2Option);

	//__ARROW CHAR
	mArrowChar.setTexture(getContext().textures->get(Textures::Arrow));
	mArrowChar.setOrigin(mArrowChar.getLocalBounds().width, mArrowChar.getLocalBounds().height / 2.f);
	mArrowChar.setPosition(charOptions[charOptionIndex].getPosition() - sf::Vector2f(120.f, 10.f));

	charOptions.push_back(backOption);


	updateOption();
}

void LevelSelectState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	//window.draw(backgroundSprite); 

	window.draw(backgroundSprite);
	
	//Draw all options except the "Back"
	for (int i = 0; i < levelOptions.size() - 1; i++) {
		sf::Sprite& sprite = levelOptions[i];
		window.draw(sprite);
	}

	for (int i = 0; i < charOptions.size() - 1; i++) {
		sf::Sprite& sprite = charOptions[i];
		window.draw(sprite);
	}

	window.draw(mArrow);

	if(mIsLevelSelected) window.draw(mArrowChar);

	//Only draw 1 back button
	if (!mIsLevelSelected) {
		window.draw(levelOptions[levelOptions.size() - 1]);
	}
	else {
		window.draw(charOptions[charOptions.size() - 1]);
	}
	
}

bool LevelSelectState::update(sf::Time dt)
{
	return false;
}

bool LevelSelectState::handleEvent(const sf::Event& event)
{
	//hardcoded for now, might change later
	if (!mIsLevelSelected) {
		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
			if (levelOptionIndex) --levelOptionIndex;
			else levelOptionIndex = levelOptions.size() - 1;
			getContext().sounds->play(SoundEffect::ChangeOption);
			updateOption();
		}
		else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
			if (levelOptionIndex < levelOptions.size() - 1) ++levelOptionIndex;
			else levelOptionIndex = 0;
			getContext().sounds->play(SoundEffect::ChangeOption);
			updateOption();
		}
		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Return) {
			if (levelOptionIndex + 2 == Back) {
				requestStackPop(); 
			}
			else if (levelOptionIndex == Level1 || levelOptionIndex == Level2 || levelOptionIndex == Level3) {
				mIsLevelSelected = true;
				updateOption();
			}
		}
	}
	else if (mIsLevelSelected) {
		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
			if (charOptionIndex) --charOptionIndex;
			else charOptionIndex = charOptions.size() - 1;
			getContext().sounds->play(SoundEffect::ChangeOption);
			updateOption();
		}
		else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
			if (charOptionIndex < charOptions.size() - 1) ++charOptionIndex;
			else charOptionIndex = 0;
			getContext().sounds->play(SoundEffect::ChangeOption);
			updateOption();
		}
		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Return) {
			if (charOptionIndex + 3 == Character1) {
				if (levelOptionIndex == Level1) {
					requestStateClear(); 
					requestStackPushGame(World::Snapshot(Characters::Character1, Level::Easy));
					
				}
				if (levelOptionIndex == Level2) {
					requestStateClear();
					requestStackPushGame(World::Snapshot(Characters::Character1, Level::Medium));
					
				}
				if (levelOptionIndex == Level3) {
					requestStateClear();
					requestStackPushGame(World::Snapshot(Characters::Character1, Level::Hard));
					
				}
			}
			if (charOptionIndex + 3 == Character2) {
				if (levelOptionIndex == Level1) {
					requestStateClear();
					requestStackPushGame(World::Snapshot(Characters::Character2, Level::Easy));
				}
				if (levelOptionIndex == Level2) {
					requestStateClear();
					requestStackPushGame(World::Snapshot(Characters::Character2, Level::Medium));
				}
				if (levelOptionIndex == Level3) {
					requestStateClear(); 
					requestStackPushGame(World::Snapshot(Characters::Character2, Level::Hard));
		
				}
			}
			if (charOptionIndex + 3 == Back) {
				mIsLevelSelected = false;
				updateOption();
			}


		}
		
	}
	
	return false;
}

void LevelSelectState::updateOption()
{
	if (levelOptions.empty() || charOptions.empty()) return;

	// Reset texture rects for all options
	for (sf::Sprite& sprite : levelOptions) {
		sprite.setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));
	}

	// Highlight the selected option
	sf::IntRect textureRect = levelOptions[levelOptionIndex].getTextureRect();
	textureRect.top += textureRect.height;
	levelOptions[levelOptionIndex].setTextureRect(textureRect);

	// Update the arrow position to point at the selected option
	mArrow.setPosition(levelOptions[levelOptionIndex].getPosition() - sf::Vector2f(150.f, 10.f));

	// Reset texture rects for all char
	for (int i = 0; i < charOptions.size() - 1; i++){
		sf::Sprite& sprite = charOptions[i];
		sprite.setTextureRect(sf::IntRect(0, 0, mCharSize.x, mCharSize.y));
	}

	charOptions[charOptions.size() - 1].setTextureRect(sf::IntRect(0, 0, mButtonSize.x, mButtonSize.y));

	// Highlight the selected option
	if (mIsLevelSelected){
		sf::IntRect textureRectChar = charOptions[charOptionIndex].getTextureRect();
		textureRectChar.top += textureRectChar.height;
		charOptions[charOptionIndex].setTextureRect(textureRectChar);
	}
	

	// Update the arrow position to point at the selected option
	mArrowChar.setPosition(charOptions[charOptionIndex].getPosition() - sf::Vector2f(150.f, 10.f));
}