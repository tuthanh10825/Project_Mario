#include "Player.h"
#include "ID.h"
#include "Character.h"

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if ((event.key.code == sf::Keyboard::Space) && (event.type == event.KeyPressed)) {
		Command jump;
		jump.category = Category::Player;
		jump.action = [=](SceneNode& s, sf::Time dt) {

			Character& mainChar = static_cast<Character&> (s);
			if (!mainChar.isAir() && !mainChar.isJump())
			{
				mainChar.setJump(true);
			}
			};
		commands.push(jump);
	}
	if (event.key.code == sf::Keyboard::Left) {
		if (event.type == event.KeyPressed) {
			Command moveLeft;
			moveLeft.category = Category::Player;
			moveLeft.action = [=](SceneNode& s, sf::Time dt) {
				Character& mainChar = static_cast<Character&>(s);
				mainChar.setMoveLeft(true); 
			};
			commands.push(moveLeft);
		}
		else if (event.type == event.KeyReleased) {
			Command stopLeft; 
			stopLeft.category = Category::Player;
			stopLeft.action = [=](SceneNode& s, sf::Time dt) {
				Character& mainChar = static_cast<Character&>(s);
				mainChar.setMoveLeft(false);
				}; 
			commands.push(stopLeft); 
		}
	}
	if (event.key.code == sf::Keyboard::Right) {
		if (event.type == event.KeyPressed) {
			Command moveRight;
			moveRight.category = Category::Player;
			moveRight.action = [=](SceneNode& s, sf::Time dt) {
				Character& mainChar = static_cast<Character&>(s);
				mainChar.setMoveRight(true);
				};
			commands.push(moveRight);
		}
		else if (event.type == event.KeyReleased) {
			Command stopRight;
			stopRight.category = Category::Player;
			stopRight.action = [=](SceneNode& s, sf::Time dt) {
				Character& mainChar = static_cast<Character&>(s);
				mainChar.setMoveRight(false);
				};
			commands.push(stopRight);
		}
	}
	
	
}

void Player::handleRealtimeInput(CommandQueue& command)
{
	
	//TODO: adding function when the right is released.
}
