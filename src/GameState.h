#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"
#include <nlohmann/json.hpp>
using json=nlohmann::json; 
class State; 
class GameState : public State {
public: 
	GameState(StateStack& stack, Context context);
	virtual void draw(); 
	virtual bool update(sf::Time dt); 
	virtual bool handleEvent(const sf::Event& event); 
	void setLevel(Level level, Character::Type type);
private: 
	json mapsConfig; 
	World world; 
	Player& player;
	Hub hub; 

	Level currLevel; 
	Characters currChar; 
};