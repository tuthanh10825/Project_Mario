#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"
class GameState : public State {
public: 
	GameState(StateStack& stack, Context context);
	virtual void draw(); 
	virtual bool update(sf::Time dt); 
	virtual bool handleEvent(const sf::Event& event); 
private: 
	World world; 
	Player& player;
};