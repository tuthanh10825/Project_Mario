#include "GameState.h"
#include <fstream>
#include <iostream>

GameState::GameState(StateStack& stack, Context context) : State(stack, context)
	, world(*context.window, *context.textures, *context.fonts, *context.sounds)
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
}

bool GameState::update(sf::Time dt)
{
	world.update(dt); 
	if (!world.hasAlivePlayer()) {
		getContext().musics->setPaused(true); 
		getContext().sounds->play(SoundEffect::Die); 
		sf::sleep(sf::seconds(3)); 
		getContext().musics->setPaused(false); 

		requestStackPushDeath(world.createSnapshot());
	}

	if (world.playerReachBound()) // winning condition
	{
		getContext().musics->setPaused(true);
		getContext().sounds->play(SoundEffect::Win);
		sf::sleep(sf::seconds(5));
		getContext().musics->setPaused(false); 

		requestStackPop(); 
		requestStackPush(States::Win); 
	}
	return false; 
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape) {
		requestStackPushPause(world.createSnapshot()); 
		return false; 
	}
	CommandQueue& commands = world.getCommandQueue(); 
	player.handleRealtimeInput(commands);
	player.handleEvent(event, commands); 
	return false; 

}


void GameState::applySnapshot(World::Snapshot snapshot)
{
	world.loadWorld(mapsConfig["levels"], snapshot); 
}
