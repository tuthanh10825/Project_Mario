#include "Player.h"
#include "ID.h"
#include "Character.h"

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
}

void Player::handleRealtimeInput(CommandQueue& command)
{
	const float playerSpeed = 120.f; 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		Command moveLeft; 
		moveLeft.category = Category::Player; 
		moveLeft.action = [=](SceneNode& s, sf::Time dt) {
			Character& mainChar = static_cast<Character&>(s);
			mainChar.move(-playerSpeed * dt.asSeconds(), 0);
			}; 
		command.push(moveLeft); 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		Command moveRight; 
		moveRight.category = Category::Player; 
		moveRight.action = [=](SceneNode& s, sf::Time dt) {
			Character& mainChar = static_cast<Character&>(s);
			mainChar.move(playerSpeed * dt.asSeconds(), 0);
			};
		command.push(moveRight); 
	}
}
