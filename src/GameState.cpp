#include "GameState.h"
#include <fstream>
#include <iostream>

GameState::GameState(StateStack& stack, Context context) : State(stack, context), hub(context), currLevel(Level::None), currChar(Characters::CharNone)
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
		getContext().musics->setPaused(true); 
		getContext().sounds->play(SoundEffect::Die); 
		sf::sleep(sf::seconds(3)); 
		getContext().musics->setPaused(false); 

		requestStackPushDeath(currLevel, currChar);
	}

	if (world.playerReachBound()) // winning condition
	{
		getContext().musics->setPaused(true);
		getContext().sounds->play(SoundEffect::Win);
		sf::sleep(sf::seconds(5));
		getContext().musics->setPaused(false); 
		requestStackPush(States::Win); 
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

void GameState::setLevel(Level level, Character::Type type)
{
	currLevel = level; 
	if (type == Character::Character1) currChar = Characters::Character1;
	else if (type == Character::Character2) currChar = Characters::Character2; 

	world.loadWorld(mapsConfig["levels"][level - 1], type);
}

