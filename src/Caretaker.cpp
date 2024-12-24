#include "Caretaker.h"
#include <iostream>
Caretaker::Caretaker()
{
	std::ifstream fin("saves.json", std::ios_base::binary); 
	if (!fin.is_open())
		throw; 
	json saves = json::parse(fin); 
	for (auto& games : saves) {
		std::cout << games; 
		recentGames.push_back(World::Snapshot(games["Character"], games["Level"], sf::Vector2f(games["position"]["x"], games["position"]["y"])));
	}
}

Caretaker::~Caretaker()
{
	json out;
	int i = 0;
	for (auto it = recentGames.begin(); it != recentGames.end(); ++it, ++i) {
		out[i]["Character"] = it->getCharacterType();
		out[i]["Level"] = it->getLevel();
		out[i]["position"]["x"] = it->getPlayerPos().x;
		out[i]["position"]["y"] = it->getPlayerPos().y; 
	}
	std::ofstream fout("saves.json"); 
	fout << out; 
}

void Caretaker::push(World::Snapshot snapshot)
{
	recentGames.push_front(snapshot); 
	while (recentGames.size() > 5)
		recentGames.pop_back(); 
}

const World::Snapshot Caretaker::getSnapshot(std::size_t index) const
{
	assert(index < recentGames.size());
	auto ans = recentGames.begin(); 
	for (int i = 0; i < index; ++i)
		++ans; 
	return *ans; 
}

const std::size_t Caretaker::size() const
{
	return recentGames.size(); 
}

