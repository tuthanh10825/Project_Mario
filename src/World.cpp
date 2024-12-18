#include "World.h"
#include <iostream>
#include <cassert>
World::World(sf::RenderWindow& window, TextureHolder& textures, Hub& hub) : window(window), worldView(window.getDefaultView()), textures(textures),
spawnPosition(worldView.getSize().x / 2.f, worldView.getSize().y / 2.f),
character(nullptr),
scrollSpeed(80.f), 
hub(hub),
time(0)
{
	loadTextures();
	worldView.setCenter(spawnPosition);

	applyGravity.category = Category::Player | Category::Enemy | Category::Pickup;
	applyGravity.action = [](SceneNode& s, sf::Time dt) {
		Entity& entity = static_cast<Entity&> (s);
		sf::Vector2f accel = entity.getAcceleration();
		sf::Vector2f velocity = entity.getVelocity();

		if (entity.isAir()) {
			entity.setAcceleration(accel.x, 1000.f);
		}
		else {
			entity.setAcceleration(accel.x, 0);
			if (velocity.y > 0)
				entity.setVelocity(velocity.x, 0);
		}
	};

	setAir.category = Category::Player | Category::Enemy | Category::Pickup;
	setAir.action = [](SceneNode& s, sf::Time dt) {
		Entity& entity = static_cast<Entity&> (s);
		entity.setAir(true);
	};
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

	
	//handle player input here. 
	
	commandQueue.push(applyGravity); 
	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt);
	}
	

	//handleCollisions(); 

	//this will handle the player velocity during the gameplay.  
	adaptPlayerVelocity();
	sceneGraph.onCommand(setAir, dt);
	handleCollisions();
	
	sceneGraph.onCommand(applyGravity, dt);
	//update first
	if (character->canFire()) {
		commandQueue.push(character->getFireCommand());
	}

	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt);
	}
	

	/*sf::Vector2f charPos = character->getPosition();
	std::cout << "After updating: " << charPos.x << " " << charPos.y << std::endl;*/
	sceneGraph.removeDestroyObjects();
	sceneGraph.update(dt);
	//Collision next


	////set Worldview here ? 
	updatePlayerView(dt); 
	hub.setTime((time += dt.asSeconds()));
	hub.setHP(character->getHp()); 
}
void World::adaptPlayerVelocity()
{
	const float accel_x = 600.f;
	const float friction = 1500.f;

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
	textures.load(Textures::Pickup, "textures/mushroom.png"); 
	textures.load(Textures::Projectile, "textures/Projectile.png");
}

void World::buildScene(json& info) // we need to load the "front" world here.
{
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}
	sceneLayers[Air]->setCategory(Category::SceneNodeAir);

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
	

		if (blockInfo["src"][0] == 540) {
			std::unique_ptr<MysteryBlock> block(new MysteryBlock(blockTexture)); 
			block->setPosition(sf::Vector2f(blockInfo["px"][0], blockInfo["px"][1]));
			block->addItem(Pickup::Type::mushroom);
			sceneLayers[Air]->attachChild(std::move(block));
		}
		else if (blockInfo["src"][0] == 600) {
			enemyInfo.push_back({ Enemy::Goomba, sf::Vector2f(blockInfo["px"][0], blockInfo["px"][1]) });
		}
		else {
			std::unique_ptr<Block> block(new Block(blockTexture));
			block->setPosition(sf::Vector2f(blockInfo["px"][0], blockInfo["px"][1]));
			sceneLayers[Air]->attachChild(std::move(block));
		}
	}
	sort(enemyInfo.begin(), enemyInfo.end(), std::greater<EnemyInfo>());
	hub.setHP(character->getHp()); 
}

void World::setWorldBound(sf::FloatRect& rect)
{
	worldBounds = rect; 
}

const sf::View& World::getView() const
{
	return worldView;
}
bool World::hasAlivePlayer() const
{
	return !character->isDestroyed();
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs; 
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs); 
	bool isAir = true; 
	sf::Vector2f charVelocity = character->getVelocity();
	sf::Vector2f charAccel = character->getAcceleration();
	for (SceneNode::Pair pair : collisionPairs) {

		if (matchesCategories(pair, Category::Player, Category::MysteryBlock)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			adjustChar(*pair.second, direction);


			if (direction == Collision::Down) {
				charVelocity.y = 0;
				static_cast<MysteryBlock&>(*pair.second).setMove(-character->getVelocity().y);
				Command createPickupCommand; 
				createPickupCommand.category = Category::SceneNodeAir; 
				createPickupCommand.action = [pair, this](SceneNode& node, sf::Time) {
					static_cast<MysteryBlock&>(*pair.second).createPickup(node, textures);
				};
				commandQueue.push(createPickupCommand);
			}
			else if (direction == Collision::Up && charVelocity.y >= -10) {
				isAir = false;
			}
			else if ((direction == Collision::Left) && charVelocity.x > 0) {
				charVelocity.x = 0;
				charAccel.x = 0;
			}
			else if ((direction == Collision::Right) && charVelocity.x < 0) {
				charVelocity.x = 0;
				charAccel.x = 0;
			}
			
		}

		if (matchesCategories(pair, Category::Player, Category::Block)) {
			//handle the collision
			Collision::Direction direction = collisionType(*character, *pair.second);
			adjustChar(*pair.second, direction);

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
		
		}

		if (matchesCategories(pair, Category::Player, Category::Enemy)) {
			//handle the collision
			Collision::Direction direction = collisionType(*character, *pair.second);
			adjustChar(*pair.second, direction);
			Enemy& enemy = static_cast<Enemy&>(*pair.second);

			if (direction == Collision::Up && charVelocity.y >= -10) {
				isAir = false;
			}
			else if (direction == Collision::Down && charVelocity.y < 0) {
				charVelocity.y = 0;
				character->damage(enemy.getHp());
			}
			else if ((direction == Collision::Left) && charVelocity.x > 0) {
				charVelocity.x = 0;
				charAccel.x = 0;
				character->damage(enemy.getHp());
			}
			else if ((direction == Collision::Right) && charVelocity.x < 0) {
				charVelocity.x = 0;
				charAccel.x = 0;
				character->damage(enemy.getHp());
			}
		}

		if (matchesCategories(pair, Category::Player, Category::Pickup)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& pickup = static_cast<Pickup&>(*pair.second);
			pickup.destroy();
			pickup.apply(*character);
		}

		// enemy and block collision
		if (matchesCategories(pair, Category::Enemy, Category::Block)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& enemy = static_cast<Enemy&>(*pair.first);
			adjustEnemy(enemy, *pair.second, direction);

			if (direction == Collision::Left) {
				enemy.setMoveLeft(true);
				enemy.setMoveRight(false);
			}
			else if (direction == Collision::Right) {
				enemy.setMoveRight(true);
				enemy.setMoveLeft(false);
			}
			if (direction == Collision::Up) {
				enemy.setAir(false);
			}
		}

		// enemy and movable block collision
		if (matchesCategories(pair, Category::Enemy, Category::MysteryBlock)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& enemy = static_cast<Enemy&>(*pair.first);
			adjustEnemy(enemy, *pair.second, direction);

			if (direction == Collision::Left) {
				enemy.setMoveLeft(true);
				enemy.setMoveRight(false);
			}
			else if (direction == Collision::Right) {
				enemy.setMoveRight(true);
				enemy.setMoveLeft(false);
			}
			if (direction == Collision::Up) {
				enemy.setAir(false);
			}
		}

		// enemy and enemy collision
		if (matchesCategories(pair, Category::Enemy, Category::Enemy)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& enemy1 = static_cast<Enemy&>(*pair.first);
			auto& enemy2 = static_cast<Enemy&>(*pair.second);
			if (enemy1.isDestroyed()) continue;
			if (enemy2.isDestroyed()) continue;

			if (direction == Collision::Left) {
				enemy1.setMoveLeft(true);
				enemy1.setMoveRight(false);
				enemy2.setMoveRight(true);
				enemy2.setMoveLeft(false);
			}
			else if (direction == Collision::Right) {
				enemy1.setMoveRight(true);
				enemy1.setMoveLeft(false);
				enemy2.setMoveLeft(true);
				enemy2.setMoveRight(false);
			}
			if (direction == Collision::Up) {
				enemy1.setAir(false);
				enemy2.setAir(false);
			}
		}

		// enemy and player collision
		if (matchesCategories(pair, Category::Enemy, Category::Player)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& enemy = static_cast<Enemy&>(*pair.first);
			if (direction == Collision::Down) {
				enemy.setMoveRight(false);
				enemy.setMoveLeft(false);
				enemy.setScale(1, 0.5);
				enemy.move(0, 12);
				enemy.destroy();
			}
		}
		if (matchesCategories(pair, Category::Pickup, Category::MysteryBlock)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& pickup = static_cast<Pickup&>(*pair.first);
			adjustPickup(pickup, *pair.second, direction);
			if (direction == Collision::Up) {
				if (pickup.getVelocity().y >= 0 && pickup.getVelocity().x == 0) {
					pickup.setMoveRight(true);
				}
				pickup.setAir(false);
			}
			if (direction == Collision::Right) {
				pickup.setMoveRight(true);
				pickup.setMoveLeft(false);
			}
			if (direction == Collision::Left) {
				pickup.setMoveLeft(true);
				pickup.setMoveRight(false);
			}
		}
		if (matchesCategories(pair, Category::Pickup, Category::Block)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& pickup = static_cast<Pickup&>(*pair.first);
			adjustPickup(pickup, *pair.second, direction);
			if (direction == Collision::Up) {
				pickup.setAir(false);
			}
			if (direction == Collision::Right) {
				pickup.setMoveRight(true);
				pickup.setMoveLeft(false);
			}
			if (direction == Collision::Left) {
				pickup.setMoveLeft(true);
				pickup.setMoveRight(false);
			}
		}
		if (matchesCategories(pair, Category::Pickup, Category::Enemy)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& pickup = static_cast<Pickup&>(*pair.first);
			auto& enemy = static_cast<Enemy&>(*pair.second);
			adjustPickup(pickup, *pair.second, direction);
			if (direction == Collision::Left) {
				pickup.setMoveLeft(true);
				pickup.setMoveRight(false);
				enemy.setMoveLeft(false);
				enemy.setMoveRight(true);
			}
			else if (direction == Collision::Right) {
				pickup.setMoveRight(true);
				pickup.setMoveLeft(false);
				enemy.setMoveRight(false);
				enemy.setMoveLeft(true);
			}
		}

		if (matchesCategories(pair, Category::Pickup, Category::Pickup)) {
			Collision::Direction direction = collisionType(*pair.first, *pair.second);
			auto& pickup1 = static_cast<Pickup&>(*pair.first);
			auto& pickup2 = static_cast<Pickup&>(*pair.second);
			if (direction == Collision::Left) {
				pickup1.setMoveLeft(true);
				pickup1.setMoveRight(false);
				pickup2.setMoveRight(true);
				pickup2.setMoveLeft(false);
			}
			else if (direction == Collision::Right) {
				pickup1.setMoveRight(true);
				pickup1.setMoveLeft(false);
				pickup2.setMoveLeft(true);
				pickup2.setMoveRight(false);
			}
			if (direction == Collision::Up) {
				pickup1.setAir(false);
				adjustPickup(pickup1, *pair.second, direction);
			}
			else if (direction == Collision::Down) {
				pickup2.setAir(false);
				adjustPickup(pickup2, *pair.first, direction);
			}
			else adjustPickup(pickup1, *pair.second, direction);
		}
	}

	character->setVelocity(charVelocity);
	character->setAcceleration(charAccel);
	character->setAir(isAir);
}
void World::updatePlayerView(sf::Time dt)
{
	sf::Vector2f windowSize = worldView.getSize();
	sf::Vector2f after = character->getWorldPosition();
	if (after.x + windowSize.x / 2 > worldBounds.getSize().x || after.x - windowSize.x / 2 < 0) return;
	else worldView.move(sf::Vector2f(character->getVelocity().x * dt.asSeconds(), 0.f));

	//TODO: refactoring
	while (enemyInfo.size() && enemyInfo.back().position.x > after.x - windowSize.x / 2 && enemyInfo.back().position.x < after.x + windowSize.x / 2) {
		EnemyInfo enemy = enemyInfo.back();
		enemyInfo.pop_back();
		std::unique_ptr<Enemy> tempEnemy(new Enemy(enemy.type, textures));
		tempEnemy->setPosition(enemy.position);
		enemies.push_back(tempEnemy.get());
		sceneLayers[Air]->attachChild(std::move(tempEnemy));
	}
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

void World::adjustEnemy(Enemy& enemy, SceneNode& node, Collision::Direction direction) {
	sf::FloatRect enemyBox = enemy.getBoundingRect();
	sf::FloatRect nodeBox = node.getBoundingRect();

	sf::Vector2f enemyCenter = enemyBox.getPosition() + enemyBox.getSize() / 2.f;
	sf::Vector2f nodeCenter = nodeBox.getPosition() + nodeBox.getSize() / 2.f;

	float dx = nodeCenter.x - enemyCenter.x;
	float dy = nodeCenter.y - enemyCenter.y;

	sf::Vector2f dv(dx, dy);
	if (direction == Collision::Right || direction == Collision::Left) {
		float offset = enemyBox.width / 2 + nodeBox.width / 2 - std::abs(dx);
		if (direction == Collision::Left) offset *= -1;
		enemy.move(offset, 0);
	}
	else if (direction == Collision::Up || direction == Collision::Down) {
		float offset = enemyBox.height / 2 + nodeBox.height / 2 - std::abs(dy);
		if (direction == Collision::Up) offset *= -1;
		enemy.move(0, offset);
	}
}

void World::adjustPickup(Pickup& pickup, SceneNode& node, Collision::Direction direction) {
	sf::FloatRect pickupBox = pickup.getBoundingRect();
	sf::FloatRect nodeBox = node.getBoundingRect();

	sf::Vector2f pickupCenter = pickupBox.getPosition() + pickupBox.getSize() / 2.f;
	sf::Vector2f nodeCenter = nodeBox.getPosition() + nodeBox.getSize() / 2.f;

	float dx = nodeCenter.x - pickupCenter.x;
	float dy = nodeCenter.y - pickupCenter.y;

	sf::Vector2f dv(dx, dy);
	if (direction == Collision::Right || direction == Collision::Left) {
		float offset = pickupBox.width / 2 + nodeBox.width / 2 - std::abs(dx);
		if (direction == Collision::Left) offset *= -1;
		pickup.move(offset, 0);
	}
	else if (direction == Collision::Up || direction == Collision::Down) {
		float offset = pickupBox.height / 2 + nodeBox.height / 2 - std::abs(dy);
		if (direction == Collision::Up) offset *= -1;
		pickup.move(0, offset);
	}
}


bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
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
