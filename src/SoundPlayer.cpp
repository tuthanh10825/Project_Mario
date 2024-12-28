#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : soundBuffers(), sounds(), volume(100)
{
	soundBuffers.load(SoundEffect::ChangeOption, "music/change-option.wav"); 
	soundBuffers.load(SoundEffect::Jump, "music/jump-small.wav"); 
	soundBuffers.load(SoundEffect::Pause, "music/pause.wav"); 
	soundBuffers.load(SoundEffect::Fire, "music/fireworks.wav"); 
	soundBuffers.load(SoundEffect::Die, "music/death.wav");
	soundBuffers.load(SoundEffect::Win, "music/win.wav");
	soundBuffers.load(SoundEffect::CreateMushroom, "music/coin.wav"); 
	soundBuffers.load(SoundEffect::CreateFlower, "music/coin.wav"); 
	soundBuffers.load(SoundEffect::CreateCoin, "music/coin.wav"); 
	soundBuffers.load(SoundEffect::EnemyDeath, "music/bump.wav"); 
	soundBuffers.load(SoundEffect::CharacterDeath, "music/entitydeath.wav"); 
	soundBuffers.load(SoundEffect::GetPickup, "music/kick.wav"); 
}
void SoundPlayer::play(SoundEffect::ID effect) {
	sounds.push_back(sf::Sound(soundBuffers.get(effect))); 
	sounds.back().setVolume(volume); 
	sounds.back().play(); 
}

void SoundPlayer::removeStoppedSounds() {
	sounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
		});
}

float SoundPlayer::getVolume() const
{
	return volume; 
}

void SoundPlayer::setVolume(int volumeLevel) {
	volume = volumeLevel;
}