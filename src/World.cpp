#include "World.h"

World::World(sf::RenderWindow& window) : window(window), worldView(window.getDefaultView()), 
	worldBounds(
		0.f, 
		0.f, 
		3000.f, 
		worldView.getSize().y
		), 
	spawnPosition(worldView.getSize().x / 2.f, worldView.getSize().y / 2.f), 
	player(nullptr), 
	scrollSpeed(80.f)
{
	loadTextures(); 
	buildScene(); 

	worldView.setCenter(spawnPosition); 
}

void World::draw()
{
	window.setView(worldView); 
	window.draw(sceneGraph); 
}

void World::update(sf::Time dt) {
	worldView.move(scrollSpeed * dt.asSeconds(), 0.f); 
	sf::Vector2f position = player->getPosition(); 
	sf::Vector2f velocity = player->getVelocity(); 

	if (position.y <= worldBounds.top||
		position.y >= worldBounds.top + worldBounds.height - 150) {
		velocity.y = -velocity.y; 
		player->setVelocity(velocity); 
	}

	sceneGraph.update(dt); 
}

void World::loadTextures()
{
	textures.load(Textures::Background, "textures/background.jpg"); 
	textures.load(Textures::Character1, "textures/character1.png"); 

}

void World::buildScene()
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

		std::unique_ptr<Player> tempPlayer(new Player(Player::Character1, textures)); 

		player = tempPlayer.get(); 
		player->setPosition(spawnPosition); 
		player->setVelocity(80.f, scrollSpeed); 

		sceneLayers[Air]->attachChild(std::move(tempPlayer)); 

}
