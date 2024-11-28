#include "GameState.h"

GameState::GameState(StateStack& stack, Context context) : State(stack, context), world(*context.window, *context.textures), player(*context.player)
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
	if (event.key.code == sf::Keyboard::Escape) {
		requestStackPush(States::Pause);
		return true; 
	}
	CommandQueue& commands = world.getCommandQueue(); 
	player.handleEvent(event, commands); 
	player.handleRealtimeInput(commands); 
	return true; 
}
