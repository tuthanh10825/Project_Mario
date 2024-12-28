#pragma once
#include "ResourceHolder.h"
#include <list>
class SoundPlayer : private sf::NonCopyable {
public: 
	SoundPlayer(); 
	void play(SoundEffect::ID effect); 
	void setVolume(int volumeLevel);
	void removeStoppedSounds();
	float getVolume() const;
	float volume;
private: 
	SoundBufferHolder soundBuffers; 
	std::list<sf::Sound> sounds; 
};