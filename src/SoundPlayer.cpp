#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : soundBuffers(), sounds()
{
	soundBuffers.load(SoundEffect::ChangeOption, "music/change-option.wav"); 
	soundBuffers.load(SoundEffect::Jump, "music/jump-small.wav"); 
	soundBuffers.load(SoundEffect::Pause, "music/pause.wav"); 
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