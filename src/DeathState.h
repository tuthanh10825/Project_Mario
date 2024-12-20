﻿#pragma once
#include "StateStack.h"

class DeathState : public State {
private:
    enum OptionNames {
        Retry,
        Exit,
    };

    sf::RectangleShape backgroundShape;
    std::vector<sf::Text> options;
    std::size_t optionIndex;

    SoundPlayer die;
    SoundPlayer gameOver;
public:
    DeathState(StateStack& stateStack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void updateOptionText();
};
