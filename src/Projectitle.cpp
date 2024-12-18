#include "Projectitle.h"
#include <iostream>

Projectitle::Projectitle(Type type, TextureHolder& textures)
	: Entity(1)
	, type(type)
	, damage(1)
	, isTouchGround(false)
{
	sf::Texture& texture = textures.get(Textures::Projectile);
	sf::Vector2u boundaryRect = texture.getSize();
	sprite.setTexture(&texture);
	sprite.setSize(sf::Vector2f(boundaryRect.x, boundaryRect.y));
	sprite.setOrigin(sf::Vector2f(boundaryRect.x / 2.f, boundaryRect.y / 2.f));
#if _DEBUG
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setOutlineThickness(-2);
#endif // _DEBUG
	maxHeight = this->getPosition().y;
}

void Projectitle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned Projectitle::getCategory() const
{
	if (type == CharBullet) {
		return Category::Player;
	}
	else {
		return Category::Enemy;
	}
}

sf::FloatRect Projectitle::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Projectitle::updateCurrent(sf::Time dt)
{
	sf::Vector2f currVecl = this->getVelocity();
	if (isTouchGround) {
		this->setVelocity(currVecl.x, currVecl.y * -1);
	}
	if (this->getPosition().y > maxHeight) {
		this->setVelocity(currVecl.x, currVecl.y);
	}
	Entity::updateCurrent(dt);
}

int Projectitle::getDamage() const
{
	return damage;
}

void Projectitle::setDamage(int damage)
{
	this->damage = damage;
}

void Projectitle::setTouchGround(bool isTouch)
{
	isTouchGround = isTouch;
}



