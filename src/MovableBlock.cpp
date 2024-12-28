#include "MovableBlock.h"


MysteryBlock::MysteryBlock(sf::Texture& texture) : Block(texture), moving(false), movingState(MovingState::None){
	boundary.setTextureRect(sf::IntRect(0, 0, 36, 36)); 
	boundary.setSize(sf::Vector2f(36, 36));
	boundary.setOrigin(sf::Vector2f(18, 18));
}
unsigned MysteryBlock::getCategory() const
{
	return Category::MysteryBlock;
}

void MysteryBlock::setPosition(const sf::Vector2f& position)
{
	Block::setPosition(position); 
	origin = position; 
}

void MysteryBlock::setMove(float speed)
{
	if (speed > 0) {
		return;
	}
	if (movingState == MovingState::None)
	{
		this->setVelocity(0, speed);
		moving = true;
	}
}

void MysteryBlock::createPickup(SceneNode& node, TextureHolder& textures)
{
	Pickup::Type itemType = itemsType.front();
	itemsType.pop();
	std::unique_ptr<Pickup> pickup(new Pickup(itemType, textures));
	sf::Vector2f position = getWorldPosition();
	pickup->setPosition(position.x, position.y - 60.f);
	sf::Vector2f vel = getVelocity(); 
	pickup->setVelocity(vel.x, vel.y); 
	node.attachChild(std::move(pickup));
}

void MysteryBlock::updateCurrent(sf::Time dt)
{
	if (!moving) {
		return; 
	}
	else {
		if (movingState == MovingState::None) {
			movingState = MovingState::Up;
		}
		sf::Vector2f currentPosition = getWorldPosition(); 
		float speed = this -> getVelocity().y;
		if (movingState == MovingState::Up) {
			if (currentPosition.y <= origin.y - 30) {
				movingState = MovingState::Down; 
				this->setVelocity(0, -speed);
			}
		}

		if (movingState == MovingState::Down) {
			if (currentPosition.y >= origin.y) {
				Block::setPosition(origin);
				moving = false;
				if (hasItem()) {
					movingState = MovingState::None;
				}
				else {
					movingState = MovingState::Moved;
					boundary.setTextureRect(sf::IntRect(36, 0, 36, 36)); 
				}
				this->setVelocity(0, 0);
			}
		}
		
			
	}
	Entity::updateCurrent(dt);
}

bool MysteryBlock::hasItem() const
{
	return !itemsType.empty();
}

void MysteryBlock::addItem(Pickup::Type item)
{
	itemsType.push(item);
}

Pickup::Type MysteryBlock::getItem()
{
	return itemsType.front();
}