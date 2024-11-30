#pragma once
#include <set>
#include "Command.h"
#include <xutility> 
#include <memory>
#include <vector> 
#include <sfml/Graphics.hpp>
#include "ID.h"

class SceneNode : public sf::Transformable, public sf::Drawable,
	private sf::NonCopyable {
public: 
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair; 
	

public: 
	explicit SceneNode(Category::Type type = Category::None); 
	void attachChild(Ptr child); 
	Ptr detachChild(const SceneNode& node); 
	void update(sf::Time dt);
	virtual unsigned getCategory() const; 
	void onCommand(const Command& command, sf::Time dt); 

	sf::Transform getWorldTransform() const; 
	sf::Vector2f getWorldPosition() const; 

	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs); 
	void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);

	virtual sf::FloatRect getBoundingRect() const; 
private:
	virtual	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
	virtual void updateCurrent(sf::Time dt); 
	void updateChildren(sf::Time dt);


private: 
	std::vector<Ptr> children; 
	SceneNode* parent; 
	Category::Type defaultCategoryType;

};
bool collision(const SceneNode& lhs, const SceneNode& rhs);