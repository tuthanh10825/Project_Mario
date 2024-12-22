#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <functional>
#include <vector>

#include "ID.h"

class Character;

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

struct PickupData {
	std::function<void(Character&)> action;
	Textures::ID texture;
};

std::vector<EnemyData> initializeEnemyData();
std::vector<PickupData> initializePickupData();