#include "GameState.h"

GameState::GameState(StateStack& stack, Context context) : State(stack, context), world(*context.window) 
{
}

void GameState::draw()
{
	world.draw();	
}

bool GameState::update(sf::Time dt)
{
	world.update(dt); 
	return true; 
}

bool GameState::handleEvent(const sf::Event& event)
{
	return true;
}
