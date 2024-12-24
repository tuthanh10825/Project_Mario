#pragma once
#include "State.h"
class PauseState : public State {
private:
    enum OptionNames {
        Continue,
        Exit,
        VolumeSlider,
    };

    sf::RectangleShape backgroundShape;
    std::vector<sf::Sprite> options;
    std::size_t optionIndex;
    sf::Vector2i mButtonSize;


    sf::RectangleShape sliderBar;
    sf::RectangleShape sliderHandle;
    float volumeLevel;
    
    World::Snapshot lastSnapshot; 
public:
    PauseState(StateStack& stateStack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    void applySnapshot(World::Snapshot snapshot); 

private:
    void updateOptionText();
    void updateSliderAppearance();
    void decreaseVolume();
    void increaseVolume();
};