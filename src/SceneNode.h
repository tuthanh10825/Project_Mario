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
	void setCategory(Category::Type type);  // remember to use it properly 
	void onCommand(const Command& command, sf::Time dt); 

	sf::Transform getWorldTransform() const; 
	sf::Vector2f getWorldPosition() const; 

	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs); 
	void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void fixPosition(SceneNode& rhs, Collision::Direction direction); 
	
	void checkNodeIntersect(const sf::FloatRect& rect, std::vector<SceneNode*>& set);

	virtual sf::FloatRect getBoundingRect() const; 
	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;

	void removeDestroyObjects();
	
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
Collision::Direction collisionType(const SceneNode& lhs, const SceneNode& rhs); 