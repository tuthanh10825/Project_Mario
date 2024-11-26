#pragma once
#include "CommandQueue.h"
#include "SFML/Graphics.hpp"
class Player {
public: 
	void handleEvent(const sf::Event& event, CommandQueue& commands); 
	void handleRealtimeInput(CommandQueue& command); 
};