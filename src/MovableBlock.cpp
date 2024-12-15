#include "MovableBlock.h"
#include "Pickup.h"
MysteryBlock::MysteryBlock(sf::Texture& texture) : Block(texture), moving(false), movingState(MovingState::None){}
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
	this->speed = speed;
	moving = true; 
}

void MysteryBlock::createPickup(SceneNode& node, TextureHolder& textures)
{
	std::unique_ptr<Pickup> pickup(new Pickup(Pickup::Type::mushroom, textures));
	sf::Vector2f position = getWorldPosition();
	pickup->setPosition(position.x, position.y - 60.f);
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
		float speed = this -> speed; 
		if (movingState == MovingState::Up) {
			if (currentPosition.y <= origin.y - 60) {
				movingState = MovingState::Down; 
			}
			else {
				speed *= -1; 
			}
		}

		if (movingState == MovingState::Down) {
			if (currentPosition.y >= origin.y) {
				Block::setPosition(origin);
				moving = false;
				movingState = MovingState::None; 
				speed = 0; 
				return;
			}
		}
		move(0, speed * dt.asSeconds()); 
	}
}
