#include "SceneNode.h"
#include "ID.h"
#include <cassert>

SceneNode::SceneNode(Category::Type type)  : parent(nullptr), children(), defaultCategoryType(type)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->parent = this; 
	children.push_back(std::move(child)); 
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(children.begin(), children.end(), [&](Ptr& p) -> bool {
		return p.get() == (&node);
		});
	assert(found != children.end()); 

	Ptr result = std::move(*found); 
	result->parent = nullptr; 
	children.erase(found); 
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt); 
	updateChildren(dt); 
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform ans = sf::Transform::Identity; 
	for (const SceneNode* node = this; node != nullptr; node = node->parent) {
		ans = node->getTransform() * ans; 
	}
	return ans; 
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f(); 
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node))
		collisionPairs.insert(std::minmax(this, &node)); 
	for (Ptr& child : children)
		child -> checkNodeCollision(node, collisionPairs); 
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);
	for (Ptr& child : sceneGraph.children) {
		checkSceneCollision(*child, collisionPairs); 
	}
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); 
	drawCurrent(target, states); 
	for (auto it = children.begin(); it != children.end(); ++it) {
		(*it)->draw(target, states); 
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr& child : children) {
		child->update(dt); 
	}
}
unsigned SceneNode::getCategory() const {
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory()) {
		command.action(*this, dt); 
	}
	for (Ptr& child : children) {
		child->onCommand(command, dt); 
	}
}

bool collision(const SceneNode& lhs, const SceneNode& rhs) {
	sf::FloatRect boxX = lhs.getBoundingRect();
	sf::FloatRect boxY = rhs.getBoundingRect();

	sf::Vector2f centerX = boxX.getPosition() + boxX.getSize() / 2.f;
	sf::Vector2f centerY = boxY.getPosition() + boxY.getSize() / 2.f;

	float dx = centerY.x - centerX.x;
	float dy = centerY.y - centerX.y;

	float overlapX = boxX.width / 2.f + boxY.width / 2.f - std::abs(dx);
	float overlapY = boxX.height / 2.f + boxY.height / 2.f - std::abs(dy);
	if (overlapX == 0 && overlapY == 0) return false; 
	return ((overlapX >= 0) && (overlapY >= 0));

}

Collision::Direction collisionType(const SceneNode& lhs, const SceneNode& rhs)
{
	sf::FloatRect boxX = lhs.getBoundingRect(); 
	sf::FloatRect boxY = rhs.getBoundingRect();
	
	sf::Vector2f centerX = boxX.getPosition() + boxX.getSize() / 2.f; 
	sf::Vector2f centerY = boxY.getPosition() + boxY.getSize() / 2.f; 

	float dx = centerY.x - centerX.x; 
	float dy = centerY.y - centerX.y; 

	float overlapX = boxX.width / 2.f + boxY.width / 2.f - std::abs(dx); 
	float overlapY = boxX.height / 2.f + boxY.height / 2.f - std::abs(dy);

	if (overlapX >= 0 && overlapY >= 0) {
		if (overlapX >= overlapY) {
			return (dy > 0) ? Collision::Up : Collision::Down;
		}
		else return (dx > 0) ? Collision::Left : Collision::Right;
	}
	else return Collision::None; 

}
