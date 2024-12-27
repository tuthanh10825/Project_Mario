#include "Projectile.h"
#include "Utility.h"
#include <iostream>

Projectile::Projectile(Type type, TextureHolder& textures)
	: Entity(1)
	, type(type)
	, damage(1)
	, animation(textures.get(Textures::BulletAnimation))
{
	sf::Texture& texture = textures.get(Textures::Bullet);
	sf::Vector2u boundaryRect = texture.getSize();
	sprite.setTexture(&texture);
	sprite.setSize(sf::Vector2f(boundaryRect.x, boundaryRect.y));
	sprite.setOrigin(sf::Vector2f(boundaryRect.x / 2.f, boundaryRect.y / 2.f));
#if _DEBUG
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setOutlineThickness(-2);
#endif // _DEBUG
	animation.setFrameSize(sf::Vector2i(18, 18));
	animation.setNumFrames(4);
	animation.setDuration(sf::seconds(0.5));
	animation.setRepeating(true);

	centerOrigin(animation);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animation, states);
}

unsigned Projectile::getCategory() const
{
	return Category::Projectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Projectile::updateCurrent(sf::Time dt)
{
	sf::Vector2f currVecl = this->getVelocity();
	if (!isAir()) {
		this->setVelocity(currVecl.x, -300.f);
	}
	animation.update(dt);

	Entity::updateCurrent(dt);
}

int Projectile::getDamage() const
{
	return damage;
}

void Projectile::setDamage(int damage)
{
	this->damage = damage;
}




