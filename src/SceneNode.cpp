#include "SceneNode.h"
#include "ID.h"
#include <cassert>

SceneNode::SceneNode() : parent(nullptr), children()
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
