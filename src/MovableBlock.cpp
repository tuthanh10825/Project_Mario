#include "MovableBlock.h"

MovableBlock::MovableBlock(sf::Texture& texture) : Block(texture), moving(false), movingState(MovingState::None){}
unsigned MovableBlock::getCategory() const
{
	return Category::MovableBlock;
}

void MovableBlock::setPosition(const sf::Vector2f& position)
{
	Block::setPosition(position); 
	origin = position; 
}

void MovableBlock::setMove(float speed)
{
	this->speed = speed;
	moving = true; 
}

void MovableBlock::updateCurrent(sf::Time dt)
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
