#pragma once
#include "Character.h"
#include <array>
#include "ResourceHolder.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Block.h"
#include "Entity.h"
class World : private sf::NonCopyable {
public: 
	explicit World(sf::RenderWindow& window, TextureHolder& texture); 
	void update(sf::Time dt); 
	void draw(); 
	CommandQueue& getCommandQueue(); 
private:
	void loadTextures(); 
	void buildScene(); 
	void handleCollisions(); 
private: 
	enum Layer {
		Background, 
		Air, 
		LayerCount
	};
private: 
	sf::RenderWindow& window; 
	sf::View worldView; 
	TextureHolder& textures; 
	SceneNode sceneGraph; 
	std::array<SceneNode*, LayerCount> sceneLayers; 
	
	sf::FloatRect worldBounds; 
	sf::Vector2f spawnPosition; 
	float scrollSpeed; 
	Character* character; 
	CommandQueue commandQueue; 
};

bool matchesCatetgories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2); 