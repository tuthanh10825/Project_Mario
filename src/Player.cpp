#include "Player.h"
#include "ID.h"
#include "Character.h"

#include <iostream>
void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Command jump;
		jump.category = Category::Player;
		jump.action = [&](SceneNode& s, sf::Time dt) {

			Character& mainChar = static_cast<Character&> (s);
			std::cout << "mainChar is on Air: " << mainChar.isAir() << std::endl;
			if (mainChar.countJump() < 2)
			{
				mainChar.setJump(true);
				mainChar.incrJump(); 
				Command jumpSound;
				jumpSound.category = Category::SceneNodeSound;
				jumpSound.action = [=](SceneNode& s, sf::Time dt) {
					SoundNode& soundNode = static_cast<SoundNode&> (s);
					soundNode.playSound(SoundEffect::Jump);
					};
				command.push(jumpSound);
			}
		};
		std::cout << "Space is Enter" << std::endl;
		command.push(jump);

		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Command fire;
		fire.category = Category::Player;
		fire.action = [=](SceneNode& s, sf::Time dt) {
			Character& mainChar = static_cast<Character&>(s);
			if (!mainChar.isFire())
				mainChar.setFire(true);
		};
		command.push(fire);
	}
}
