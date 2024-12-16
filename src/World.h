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
using json = nlohmann::json;
class World : private sf::NonCopyable {
public: 
	explicit World(sf::RenderWindow& window, TextureHolder& texture); 
	void update(sf::Time dt); 
	void draw(); 
	CommandQueue& getCommandQueue(); 
	void buildScene(json& info);
	void setWorldBound(sf::FloatRect& rect); 
	
private:
	void adaptPlayerVelocity(); 
	void loadTextures(); 
	void handleCollisions(); 

	void removeEnemies();

	void updatePlayerView(sf::Time dt); 

	void adjustChar(SceneNode& node, Collision::Direction direction); 
	void adjustEnemy(Enemy& enemy, SceneNode& node, Collision::Direction direction);
private: 
	enum Layer {
		Background, 
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
	SceneNode sceneGraph; 
	std::array<SceneNode*, LayerCount> sceneLayers; 

	
	sf::Image tilesetImg;
	std::map<json, sf::Texture> tileset; 
	sf::FloatRect worldBounds; 
	sf::Vector2f spawnPosition; 
	float scrollSpeed; 
	Character* character; 
	CommandQueue commandQueue; 
	std::vector<EnemyInfo> enemyInfo;
	std::vector<Enemy*> enemies;
	Command applyGravity; 
};

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2); 