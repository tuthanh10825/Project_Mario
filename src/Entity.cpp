#include "Entity.h"

void Entity::setVeloctiy(sf::Vector2f velocity) {
	this->velocity = velocity; 
}
void Entity::setVelocity(float vx, float vy) {
	velecity.x = vx; 
	velocity.y = vy; 
}
sf::Vector2f Entity::getVelocity() const {
	return velocity;
}