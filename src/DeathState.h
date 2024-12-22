#pragma once
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

    Level lastLevel; 
    Characters lastChar; 

public:
    DeathState(StateStack& stateStack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    void setLevel(Level level, Characters character); 
    
private:
    void updateOptionText();
};
