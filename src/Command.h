#pragma once
#include <sfml/System.hpp>
#include <functional>
class SceneNode; 
struct Command {
	std::function<void(SceneNode&, sf::Time)> action; 
	unsigned category; 
};