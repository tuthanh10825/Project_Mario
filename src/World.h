#pragma once
#include "Player.h"
#include <array>
#include "ResourceHolder.h"
#include "SpriteNode.h"
class World : private sf::NonCopyable {
public: 
	explicit World(sf::RenderWindow& window); 
	void update(sf::Time dt); 
	void draw(); 
private:
	void loadTextures(); 
	void buildScene(); 
private: 
	enum Layer {
		Background, 
		Air, 
		LayerCount
	};
private: 
	sf::RenderWindow& window; 
	sf::View worldView; 
	TextureHolder textures; 
	SceneNode sceneGraph; 
	std::array<SceneNode*, LayerCount> sceneLayers; 
	
	sf::FloatRect worldBounds; 
	sf::Vector2f spawnPosition; 
	float scrollSpeed; 
	Player* player; 
};