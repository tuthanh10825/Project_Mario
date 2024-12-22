#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : soundBuffers(), sounds()
{
	soundBuffers.load(SoundEffect::ChangeOption, "music/change-option.wav"); 
	soundBuffers.load(SoundEffect::Jump, "music/jump-small.wav"); 
	soundBuffers.load(SoundEffect::Pause, "music/pause.wav"); 
	soundBuffers.load(SoundEffect::Fire, "music/fireworks.wav"); 
	soundBuffers.load(SoundEffect::Die, "music/death.wav");
	soundBuffers.load(SoundEffect::Win, "music/win.wav");
}
void SoundPlayer::play(SoundEffect::ID effect) {
	sounds.push_back(sf::Sound(soundBuffers.get(effect))); 
	sounds.back().play(); 
}

void SoundPlayer::removeStoppedSounds() {
	sounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
		});
}

void SoundPlayer::setVolume(int volumeLevel) {
	volumeLevel = std::clamp(volumeLevel, 0, 100);
	for (sf::Sound& sound : sounds) {
		sound.setVolume(static_cast<float>(volumeLevel));
	}
}