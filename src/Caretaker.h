#pragma once
#include <nlohmann/json.hpp>
#include "World.h"
#include <fstream> 
class Caretaker {
private: 
	std::list<World::Snapshot> recentGames; 

public: 
	Caretaker(); 
	~Caretaker(); 

	void push(World::Snapshot snapshot); 
	const World::Snapshot getSnapshot(std::size_t index) const; 
	const std::size_t size() const; 
};