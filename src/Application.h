#pragma once
#include "StateStack.h"
#include "ResourceHolder.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "LevelSelectState.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include "DeathState.h"
#include "WinState.h"
#include "ContinueState.h"
#include "Caretaker.h"
#include "SettingState.h"
class Application : sf::NonCopyable {
private: 

	static const sf::Time timePerFrame; 
	StateStack stateStack; 
	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	Player player; 
	MusicPlayer musics; 
	SoundPlayer sounds; 
	Caretaker caretaker; 

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