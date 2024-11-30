#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity; 
}
void Entity::setVelocity(float vx, float vy) {
	velocity.x = vx; 
	velocity.y = vy; 
}
void Entity::setAcceleration(sf::Vector2f accel)
{
	this->acceleration = accel;
}
void Entity::setAcceleration(float ax, float ay) {
	acceleration.x = ax; 
	acceleration.y = ay; 
}
sf::Vector2f Entity::getVelocity() const {
	return velocity;
}

sf::Vector2f Entity::getAcceleration() const
{
	return acceleration;
}

sf::FloatRect Entity::getBoundingRect() const
{
	return sf::FloatRect();
}

Entity::Entity(){
}

void Entity::updateCurrent(sf::Time dt)
{
	velocity.x += acceleration.x * dt.asSeconds(); 
	velocity.y += acceleration.y * dt.asSeconds(); 
	move(velocity.x * dt.asSeconds(), velocity.y * dt.asSeconds());

	return; 
}
