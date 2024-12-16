#include "Block.h"

class MysteryBlock : public Block {
public: 
	explicit MysteryBlock(sf::Texture& texture); 
	virtual unsigned getCategory() const override;
	void setPosition(const sf::Vector2f& position); 
	void setMove(float speed); 
	void createPickup(SceneNode& node, TextureHolder& textures); 
protected: 
	virtual void updateCurrent(sf::Time dt); 

private: 
	enum MovingState {
		Up, 
		Down, 
		None, 
	};
	MovingState movingState; 
	float speed; 
	sf::Vector2f origin; 
	bool moving;
};
