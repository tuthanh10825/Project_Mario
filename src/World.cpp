#include "World.h"
#include <iostream>
#include <cassert>
World::World(sf::RenderWindow& window, TextureHolder& textures) : window(window), worldView(window.getDefaultView()), textures(textures),
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
	
	//handle player input here. 
	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt);
	}
	assert(commandQueue.isEmpty()); 
	
	//handleCollisions(); 
	adaptPlayerVelocity(); 
	handleCollisions();
	adaptGravity(); 
	//update first

	/*sf::Vector2f charPos = character->getPosition();
	std::cout << "After updating: " << charPos.x << " " << charPos.y << std::endl;*/

	sceneGraph.update(dt);
	//Collision next
	

	////set Worldview here ? 
	sf::Vector2f after = character->getWorldPosition();
	if (after.x + windowSize.x / 2 > worldBounds.getSize().x || after.x - windowSize.x / 2 < 0) return;
	else worldView.move(sf::Vector2f(after.x - before.x, 0.f));
}

void World::adaptPlayerVelocity()
{
	const float accel_x = 600.f;
	const float friction = 1500.f;
	const float g = 1000.f;

	const float speedcap = 500.f;

	sf::Vector2f charVelocity = character -> getVelocity();
	sf::Vector2f charAccel = character -> getAcceleration();

	bool moveLeft = character->isMoveLeft(); 
	bool moveRight = character->isMoveRight(); 
	//Handle x speed
	if (moveLeft ^ moveRight) {
		if (moveLeft) {
			if (charVelocity.x > 0) {
				charAccel.x = -friction;
			}
			else if (charVelocity.x > -speedcap) {
				charAccel.x = -accel_x;
			}
			else {
				charAccel.x = 0;
				charVelocity.x = -speedcap;
			}
		}
		else {
			if (charVelocity.x < 0) {
				charAccel.x = friction;
			}
			else if (charVelocity.x < speedcap) {
				charAccel.x = accel_x;
			}
			else {
				charAccel.x = 0;
				charVelocity.x = speedcap;
			}
		}
	}
	else {
		if (charVelocity.x > 10) {
			charAccel.x = -friction;
		}
		else if (charVelocity.x < -10) {
			charAccel.x = friction;
		}
		else {
			charAccel.x = 0;
			charVelocity.x = 0;
		}
	}
	if (character->isJump()) {
		charVelocity.y = -500.f; 
		character->setJump(false); 
	}
	character -> setVelocity(charVelocity);
	character -> setAcceleration(charAccel);
}

void World::loadTextures()
{
	textures.load(Textures::Background, "textures/background.jpg");
	textures.load(Textures::Character1, "textures/idle.png");
	textures.load(Textures::MovRight, "textures/movRight.png");
	textures.load(Textures::MovLeft, "textures/movLeft.png");
	textures.load(Textures::Goomba, "textures/Goomba.png");
	textures.load(Textures::GoombaMovRight, "textures/GoombaMovLeft.png");
	textures.load(Textures::GoombaMovLeft, "textures/GoombaMovLeft.png");
	textures.load(Textures::GoombaDead, "textures/GoombaDead.png");
}

void World::buildScene(json& info) // we need to load the "front" world here.
{
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}
	//can be improved here, since the path to the background is existing. 
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
	//can be improved here, since the path to the tileset is existing. 

	assert(tilesetImg.loadFromFile("textures/tilesets.png"));

	for (auto& blockInfo : info["layerInstances"][0]["gridTiles"]) {
		
		if(tileset.find(blockInfo["src"]) == tileset.end()) {
			tileset[blockInfo["src"]].loadFromImage(tilesetImg, sf::IntRect(blockInfo["src"][0], blockInfo["src"][1], 60, 60)); 
		}
		sf::Texture& blockTexture = tileset[blockInfo["src"]];

		std::unique_ptr<Block> block(new Block(blockTexture));
		block->setPosition(sf::Vector2f(blockInfo["px"][0], blockInfo["px"][1])); 
		sceneLayers[Air]->attachChild(std::move(block)); 
	}

}

void World::setWorldBound(sf::FloatRect& rect)
{
	worldBounds = rect; 
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs; 
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs); 
	bool isAir = true; 
	for (SceneNode::Pair pair : collisionPairs) {
		if (matchesCatetgories(pair, Category::Player, Category::Block)) {


			//handle the collision
			Collision::Direction direction = collisionType(*character, *pair.second);
			adjustChar(*pair.second, direction);

			sf::Vector2f charVelocity = character->getVelocity();
			sf::Vector2f charAccel = character->getAcceleration();
			if (direction == Collision::Up && charVelocity.y >= -10) {
				isAir = false;
			}
			else if (direction == Collision::Down && charVelocity.y < 0) {
				charVelocity.y = 0;
			}
			else if ((direction == Collision::Left) && charVelocity.x > 0) {
				charVelocity.x = 0;
				charAccel.x = 0;
			}
			else if ((direction == Collision::Right) && charVelocity.x < 0) {
				charVelocity.x = 0;
				charAccel.x = 0;
			}
			character->setVelocity(charVelocity);
			character->setAcceleration(charAccel);
		}
	}
	
	character->setAir(isAir); 
}

void World::adaptGravity()
{
	bool air = character->isAir(); 
	sf::Vector2f charAccel = character->getAcceleration(); 
	sf::Vector2f charVelocity = character->getVelocity(); 
	if (air) {
		charAccel.y = 1000.f; //g
	}
	else if (!air) {
		charAccel.y = 0;
		if (charVelocity.y > 0) {
			charVelocity.y = 0; 
		}
	}
	character->setAcceleration(charAccel); 
	character->setVelocity(charVelocity); 
}

void World::adjustChar(SceneNode& node, Collision::Direction direction)
{
	sf::FloatRect charBox = character->getBoundingRect(); 
	sf::FloatRect nodeBox = node.getBoundingRect(); 
	
	sf::Vector2f charCenter = charBox.getPosition() + charBox.getSize() / 2.f; 
	sf::Vector2f nodeCenter = nodeBox.getPosition() + nodeBox.getSize() / 2.f; 

	float dx = nodeCenter.x - charCenter.x; 
	float dy = nodeCenter.y - charCenter.y; 
	
	sf::Vector2f dv(dx, dy);
	if (direction == Collision::Right || direction == Collision::Left) {
		float offset = charBox.width/ 2 + nodeBox.width / 2 - std::abs(dx);
		if (direction == Collision::Left) offset *= -1; 
		character->move(offset, 0); 
	}
	else if (direction == Collision::Up || direction == Collision::Down) {

		float offset = charBox.height / 2 + nodeBox.height / 2 - std::abs(dy);
		if (direction == Collision::Up) offset *= -1; 
		character->move(0, offset);
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
