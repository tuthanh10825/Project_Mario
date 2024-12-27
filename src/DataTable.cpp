#include "DataTable.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Character.h"


std::vector<EnemyData> initializeEnemyData()
{
	std::vector<EnemyData> data(Enemy::TypeCount);

	data[Enemy::Goomba].hp = 1;
	data[Enemy::Goomba].movLU = Textures::GoombaMove;
	data[Enemy::Goomba].movRD = Textures::GoombaMove;
	data[Enemy::Goomba].dead = Textures::GoombaDead;
	data[Enemy::Goomba].texture = Textures::Goomba;
	data[Enemy::Goomba].speed = sf::Vector2f(80.f, 0.f);
	data[Enemy::Goomba].range = sf::Vector2f(999999.f, 999999.f);
	data[Enemy::Goomba].isFly = false;
	data[Enemy::Goomba].frameSize = sf::Vector2i(36.f, 36.f);

	data[Enemy::Plant].hp = 1;
	data[Enemy::Plant].movLU = Textures::PlantMove;
	data[Enemy::Plant].movRD = Textures::PlantMove;
	data[Enemy::Plant].dead = Textures::Plant;
	data[Enemy::Plant].texture = Textures::Plant;
	data[Enemy::Plant].speed = sf::Vector2f(0.f, 30.f);
	data[Enemy::Plant].range = sf::Vector2f(0.f, 30.f);
	data[Enemy::Plant].isFly = true;
	data[Enemy::Plant].frameSize = sf::Vector2i(36.f, 54.f);

	data[Enemy::Bird].hp = 1;
	data[Enemy::Bird].movLU = Textures::BirdMovLeft;
	data[Enemy::Bird].movRD = Textures::BirdMovRight;
	data[Enemy::Bird].dead = Textures::Bird;
	data[Enemy::Bird].texture = Textures::Bird;
	data[Enemy::Bird].speed = sf::Vector2f(80.f, 0.f);
	data[Enemy::Bird].range = sf::Vector2f(80.f, 0.f);
	data[Enemy::Bird].isFly = true;
	data[Enemy::Bird].frameSize = sf::Vector2i(36.f, 36.f);


	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::Coin].action = [](Character& c) { c.incrPoint(10); };
	data[Pickup::Coin].texture = Textures::Coin;

	data[Pickup::Mushroom].action = [](Character& c) { c.heal(1); c.incrPoint(10); };
	data[Pickup::Mushroom].texture = Textures::Mushroom;

	data[Pickup::FireFlower].action = [](Character& c) { c.incrPoint(10); c.setHasFireFlower(true); };
	data[Pickup::FireFlower].texture = Textures::FireFlower;

	return data;
}

std::vector<CharacterData> initializeCharacterData()
{
	std::vector<CharacterData> data(Character::TypeCount);

	data[Character::Character1].hp = 1;
	data[Character::Character1].texture = Textures::Character1;
	data[Character::Character1].movRight = Textures::Char1MovRight;
	data[Character::Character1].movLeft = Textures::Char1MovLeft;
	data[Character::Character1].die = Textures::Character1;
	data[Character::Character1].frameSize = sf::Vector2i(36, 72);


	data[Character::Character2].hp = 1;
	data[Character::Character2].texture = Textures::Character2;
	data[Character::Character2].movRight = Textures::Char2MovRight;
	data[Character::Character2].movLeft = Textures::Char2MovLeft;
	data[Character::Character2].die = Textures::Character2;
	data[Character::Character2].frameSize = sf::Vector2i(36, 72);

	return data;
}