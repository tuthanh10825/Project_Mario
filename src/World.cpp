#include "World.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
using json = nlohmann::json; 
World::World(sf::RenderWindow& window, TextureHolder &textures) : window(window), worldView(window.getDefaultView()), textures(textures),
	worldBounds(
		0.f, 
		0.f, 
		1556.f,
		520.f
		), 
	spawnPosition(worldView.getSize().x / 2.f, worldView.getSize().y / 2.f), 
	character(nullptr), 
	scrollSpeed(80.f)
{
	loadTextures(); 
	worldView.setCenter(spawnPosition); 
}
void World::draw()
{
	window.setView(worldView); 
	window.draw(sceneGraph); 
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue; 
}

void World::update(sf::Time dt) {
	//worldView.move(scrollSpeed * dt.asSeconds(), 0.f); 
	sf::Vector2f before = character->getWorldPosition();
	sf::Vector2f windowSize = worldView.getSize();
	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt); 
	}

	//handleCollisions(); 
	
	//update first
	sceneGraph.update(dt); 
	//Collision next
	handleCollisions(); 
	
	////set Worldview here ? 
	sf::Vector2f after = character->getWorldPosition();
	if (after.x + windowSize.x / 2 > worldBounds.getSize().x || after.x - windowSize.x / 2 < 0) return; 
	else worldView.move(sf::Vector2f(after.x - before.x, 0.f));
}

void World::loadTextures()
{

	textures.load(Textures::Background, "textures/background.jpg"); 
	textures.load(Textures::Character1, "textures/idle.png"); 
	textures.load(Textures::MovRight, "textures/movRight.png");
	textures.load(Textures::MovLeft, "textures/movLeft.png");
	sf::Image tileset; 
	tileset.loadFromFile("textures/tilesets.png");
	sf::Texture floor; floor.loadFromImage(tileset, sf::IntRect(0, 0, 60, 60)); 
	textures.load(Textures::Floor, floor); 
	sf::Texture dirt; dirt.loadFromImage(tileset, sf::IntRect(60, 0, 60, 60)); 
	textures.load(Textures::Dirt, dirt); 
	sf::Texture special; special.loadFromImage(tileset, sf::IntRect(120, 0, 60, 60)); 
	textures.load(Textures::Special, special); 

	
}

void World::buildScene(Level level) // we need to load the "front" world here.
{
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}
	

	sf::Texture& background = textures.get(Textures::Background); 
	sf::IntRect textureRect(worldBounds); 

	background.setRepeated(true); 
	std::unique_ptr<SpriteNode> backgroundSprite(
		new SpriteNode(background, textureRect)
	);
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachChild(std::move(backgroundSprite)); 

	std::unique_ptr<Character> tempPlayer(new Character(Character::Character1, textures)); 
	character = tempPlayer.get(); 
	character->setPosition(spawnPosition);
	sceneLayers[Air]->attachChild(std::move(tempPlayer)); 
	std::ifstream mapInfo("testmap/test/Level_0.ldtkl");
	
	json map = json::parse(mapInfo);
	json mapData = map["layerInstances"][0]["gridTiles"];
	Textures::ID id; 
	for (auto info : mapData) {
		std::cout << info; 
		if (info["src"] == json::array({ 0, 0 })) {
			id = Textures::Floor;
		}
		else if (info["src"] == json::array({ 60, 0 })) {
			id = Textures::Dirt; 
		}
		else if (info["src"] == json::array({ 120, 0 })) {
			id = Textures::Special; 
		}
		std::unique_ptr<Block> block(new Block(textures, id)); 
		auto jsonPos = info["px"];
		block->setPosition(sf::Vector2f(jsonPos[0], jsonPos[1]));

		sceneLayers[Air]->attachChild(std::move(block)); 
	}
		
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs; 
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs); 
	for (SceneNode::Pair pair : collisionPairs) {
		if (matchesCatetgories(pair, Category::Player, Category::Block)) {
			auto& character = static_cast<Character&>(*pair.first); 
		
			character.setAir(false); 
		}
	}
}

bool matchesCatetgories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned category1 = colliders.first->getCategory(); 
	unsigned category2 = colliders.second->getCategory(); 

	if (type1 & category1 && type2 & category2) {
		return true;
	}
	else if (type1 & category2 && type2 & category1) {
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else return false; 
}
