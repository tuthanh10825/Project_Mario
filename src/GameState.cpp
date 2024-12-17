#include "GameState.h"
#include <fstream>
#include <iostream>

GameState::GameState(StateStack& stack, Context context) : State(stack, context), hub(context)
    , world(*context.window, *context.textures, hub, *context.sounds)
	, player(*context.player)
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
	hub.draw(); 
}

bool GameState::update(sf::Time dt)
{
	world.update(dt); 

	hub.updateView(world.getView()); 

	if (!world.hasAlivePlayer()) {
		requestStackPush(States::Pause);
	}

	return false; 
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape) {
		requestStackPush(States::Pause);
		return false; 
	}
	CommandQueue& commands = world.getCommandQueue(); 
	player.handleRealtimeInput(commands);
	player.handleEvent(event, commands); 
	return false; 

}

void GameState::setLevel(Level level)
{
	world.buildScene(mapsConfig["levels"][level - 1]);
}
