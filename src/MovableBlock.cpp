#include "MovableBlock.h"

MovableBlock::MovableBlock(sf::Texture& texture) : Block(texture), moving(false), movingState(MovingState::None){}
unsigned MovableBlock::getCategory()
{
	return Category::MovableBlock;
}

void MovableBlock::setPosition(const sf::Vector2f& position)
{
	Block::setPosition(position); 
	origin = position; 
}

void MovableBlock::setMove()
{
	moving = true; 
}

void MovableBlock::updateCurrent(sf::Time dt)
{
	if (!moving) {
		return; 
	}
	else {
		if (movingState == MovingState::None) {
			movingState == MovingState::Up;
		}
		sf::Vector2f currentPosition = getWorldPosition(); 
		float speed = 12; 
		if (movingState == MovingState::Down) {
			if (currentPosition.y <= origin.y) {
				Block::setPosition(origin);
				moving = false;
				return;
			}
		}
		else if (movingState == MovingState::Up) {
			speed *= -1; 
		}
		Block::move(0, speed * dt.asSeconds()); 
	}
}
