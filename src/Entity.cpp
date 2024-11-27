#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity; 
}
void Entity::setVelocity(float vx, float vy) {
	velocity.x = vx; 
	velocity.y = vy; 
}
sf::Vector2f Entity::getVelocity() const {
	return velocity;
}

Entity::Entity(bool gApplied, float g) : g(g), gApplied(gApplied)
{
}

void Entity::updateCurrent(sf::Time dt)
{
	sf::Vector2f newPosition = getPosition(); 
	if (gApplied) {
		newPosition.y = newPosition.y + 0.5 * g * dt.asSeconds() * dt.asMilliseconds(); 
	}
	setPosition(newPosition);
}
