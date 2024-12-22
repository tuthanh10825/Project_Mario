#pragma once 
#include "ID.h" 
#include <map> 
#include <SFML/System.hpp>
#include <SFML/Audio/Music.hpp>
class MusicPlayer : private sf::NonCopyable {
public: 
	MusicPlayer(); 
	void play(Music::ID theme); 
	void stop(); 

	void setPaused(bool paused); 
	void setVolume(float volume); 

	float getVolume() const; 
private: 
	sf::Music music; 
	std::map<Music::ID, std::string> filenames; 
	float volume; 
};