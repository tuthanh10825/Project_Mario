#include "World.h"

World::World(sf::RenderWindow& window, TextureHolder &textures) : window(window), worldView(window.getDefaultView()), textures(textures),
	worldBounds(
		0.f, 
		0.f, 
		3000.f, 
		worldView.getSize().y
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

	std::unique_ptr<Block> ground(new Block(textures)); 

	ground -> scale(20.f, 0.5); 
	ground->setPosition(0, worldBounds.top + worldBounds.height - ground -> getBoundingRect().height); 
	sceneLayers[Air]->attachChild(std::move(ground)); 

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
