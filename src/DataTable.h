#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <functional>
#include <vector>

#include "ID.h"

struct EnemyData {
	int hp;
	Textures::ID movLU;
	Textures::ID movRD;
	Textures::ID dead;
	Textures::ID texture;
	sf::Vector2f speed;
	sf::Vector2f range;
	bool isFly;
	sf::Vector2i frameSize;
};

std::vector<EnemyData> initializeEnemyData();