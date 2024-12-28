#pragma once
#include "StateStack.h"

class SettingState : public State {
private:
    enum OptionNames {
        Sound,
        Music,
        Exit,
    };

    sf::RectangleShape backgroundShape;
    std::vector<sf::Text> options;
    std::size_t optionIndex;

    Level lastLevel; 
    Characters lastChar; 

public:
    SettingState(StateStack& stateStack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    void applySnapshot(World::Snapshot snapshot); 
    
private:
    void updateOptionText();
};
