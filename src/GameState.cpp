#include "GameState.h"
#include <fstream>
#include <iostream>

GameState::GameState(StateStack& stack, Context context) : State(stack, context), world(*context.window, *context.textures), player(*context.player)
{
	std::ifstream file("mapsConfig.ldtk", std::ios_base::binary);
	assert(file.is_open()); 
	mapsConfig = json::parse(file); 
	sf::FloatRect worldBounds(0, 0, mapsConfig["defaultLevelWidth"], mapsConfig["defaultLevelHeight"]);
	world.setWorldBound(worldBounds);
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
	player.handleRealtimeInput(commands);
	player.handleEvent(event, commands); 
	return true; 
}

void GameState::setLevel(Level level)
{
	world.buildScene(mapsConfig["levels"][level - 1]);
}
