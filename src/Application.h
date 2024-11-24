#pragma once
#include "StateStack.h"
#include "ResourceHolder.h"
#include "MenuState.h"
class Application {
private: 
	StateStack stateStack; 
	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	
private:
	void processInput(); 
	void update(sf::Time dt); 
	void render(); 

	void registerStates(); 

public: 
	void run(); 
	Application(); 
};