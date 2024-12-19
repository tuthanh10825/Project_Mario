#pragma once
#include "State.h"

class LevelSelectState : public State {
private:
	enum OptionNames {
		Level1,
		Level2,
		Level3,
		Character1,
		Character2,
		Back,
	};
	std::vector<sf::Sprite> levelOptions;
	std::vector<sf::Sprite> charOptions;
	std::size_t levelOptionIndex;
	std::size_t charOptionIndex;
	sf::Sprite backgroundSprite;
	sf::Vector2i mButtonSize;
	sf::Vector2i mCharSize;
	sf::Sprite mArrow;
	sf::Sprite mArrowChar;

	bool mIsLevelSelected;

public:

	LevelSelectState(StateStack&, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void updateOption();
};