#include "Block.h"

class MovableBlock : public Block {
public: 
	explicit MovableBlock(sf::Texture& texture); 
	virtual unsigned getCategory(); 
	void setPosition(const sf::Vector2f& position); 
	void setMove(); 
protected: 
	virtual void updateCurrent(sf::Time dt); 
private: 
	enum MovingState {
		Up, 
		Down, 
		None, 
	};
	MovingState movingState; 
	sf::RectangleShape sprite; 
	sf::Vector2f origin; 
	bool moving;
};
