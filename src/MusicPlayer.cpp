#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() : music(), filenames(), volume(75.f) {
	filenames[Music::MenuTheme] = "music/SuperMarioBros.ogg"; 
}
void MusicPlayer::play(Music::ID theme) {
	std::string filename = filenames[theme]; 
	if (!music.openFromFile(filename)) {
		throw(std::runtime_error("Music " + filename + " could not be loaded. ")); 
	}
	music.setVolume(volume); 
	music.setLoop(true); 
	music.play(); 
}

void MusicPlayer::stop() {
	music.stop(); 
}

void MusicPlayer::setPaused(bool paused) {
	if (paused)
		music.pause();
	else music.play(); 
}

void MusicPlayer::setVolume(float volume)
{
	this->volume = volume;
}
