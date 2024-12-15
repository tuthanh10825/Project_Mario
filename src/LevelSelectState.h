#pragma once
#include "State.h"

class LevelSelectState : public State {
private:
	enum OptionNames {
		Level1,
		Level2,
		Level3,
		Back
	};
	std::vector<sf::Sprite> options;
	std::size_t optionIndex;
	sf::Sprite backgroundSprite;
	sf::Vector2i mButtonSize;
	sf::Sprite mArrow;

public:

	LevelSelectState(StateStack&, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void updateOption();
};