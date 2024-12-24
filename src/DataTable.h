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

struct CharacterData {
	int hp;
	Textures::ID texture;
	Textures::ID movRight;
	Textures::ID movLeft;
	Textures::ID die;
 	sf::Vector2i frameSize;
};

std::vector<EnemyData> initializeEnemyData();
std::vector<PickupData> initializePickupData();
std::vector<CharacterData> initializeCharacterData();