#pragma once
#include "ResourceHolder.h"
#include <list>
class SoundPlayer : private sf::NonCopyable {
public: 
	SoundPlayer(); 
	void play(SoundEffect::ID effect); 
	
	void removeStoppedSounds();

private: 
	SoundBufferHolder soundBuffers; 
	std::list<sf::Sound> sounds; 
};