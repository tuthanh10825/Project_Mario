#pragma once
#include "Character.h"
#include <array>
#include "ResourceHolder.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Block.h"
#include "MovableBlock.h"
#include "Entity.h"
#include "Enemy.h"
#include "Pickup.h"
#include <vector>
#include <nlohmann/json.hpp>
#include "Hub.h"
#include "Projectile.h"
#include "SoundNode.h" 

using json = nlohmann::json;
class World : private sf::NonCopyable {
public: 
	explicit World(sf::RenderWindow& window, TextureHolder& texture, Hub& hub, SoundPlayer& sounds); 
	void update(sf::Time dt); 
	void draw(); 

	CommandQueue& getCommandQueue();
		
	const sf::View& getView() const;

	void loadWorld(json& info, Character::Type type);
	void setWorldBound(sf::FloatRect& rect);

	bool hasAlivePlayer() const;
	bool playerReachBound() const; 
	
private:


	void buildScene();
	void loadTextures();

	void adaptPlayerVelocity(); 
	void handleCollisions(); 
	void updatePlayerView(sf::Time dt); 

	void spawnEnemies();
	/*void adjustChar(SceneNode& node, Collision::Direction direction); 
	void adjustEnemy(Enemy& enemy, SceneNode& node, Collision::Direction direction);
	void adjustPickup(Pickup& pickup, SceneNode& node, Collision::Direction direction);*/
private: 
	enum Layer {
		Background, 
		Sound,
		Entities,
		Air, 
		LayerCount
	};

	struct EnemyInfo
	{
		Enemy::Type type;
		sf::Vector2f position;

		bool operator>(const EnemyInfo& other) const
		{
			return position.x > other.position.x;
		}
	};
private: 

	sf::RenderWindow& window; 
	sf::View worldView; 
	TextureHolder& textures; 
	SoundPlayer& sounds; 

	SceneNode sceneGraph; 
	std::array<SceneNode*, LayerCount> sceneLayers; 


	sf::FloatRect worldBounds; 
	sf::Vector2f spawnPosition; 
	float scrollSpeed; 
	Character* character; 
	CommandQueue commandQueue; 
	std::vector<EnemyInfo> enemyInfo;
	std::vector<Enemy*> enemies;
	

	Hub& hub; 
	float time; 
	Command setAir;
	Command applyGravity;
	Command markingRemove; 
};

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2); 