#pragma once
#include "StateStack.h"
#include "ResourceHolder.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "LevelSelectState.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
class Application {
private: 

	static const sf::Time timePerFrame; 
	StateStack stateStack; 
	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	Player player; 
	MusicPlayer musics; 
	SoundPlayer sounds; 

private:
	void processInput(); 
	void update(sf::Time dt); 
	void render(); 

	void registerStates(); 

public: 
	void run(); 
	Application(); 
	~Application(); 
};