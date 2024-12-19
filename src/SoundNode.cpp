#include "SoundNode.h"

SoundNode::SoundNode(SoundPlayer& player) : sounds(player)
{
}

void SoundNode::playSound(SoundEffect::ID sound)
{
	sounds.play(sound); 
}

unsigned int SoundNode::getCategory() const
{
	return Category::SceneNodeSound; 
}
