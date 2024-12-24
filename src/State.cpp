#include "State.h"
#include "StateStack.h"
State::Context::Context(sf::RenderWindow& window, TextureHolder& textureHolder,
	FontHolder& fontHolder, Player& player, MusicPlayer& musics, SoundPlayer& sounds, Caretaker& caretaker) :
	window(&window), textures(&textureHolder), fonts(&fontHolder), player(&player), musics(&musics), sounds(&sounds), caretaker(&caretaker)
{

}

State::State(StateStack& stack, Context context) : stack(&stack), context(context) {}

void State::requestStackPush(States::ID stateId)
{
	stack -> pushState(stateId);
}

void State::requestStackPop()
{
	stack->popState(); 
}

void State::requestStateClear()
{
	stack->clearStates(); 
}
void State::requestStackPushGame(World::Snapshot snapshot) {
	stack->pushGameState(snapshot); 
}
void State::requestStackPushDeath(World::Snapshot snapshot)
{
	stack->pushDeathState(snapshot); 
}
void State::requestStackPushPause(World::Snapshot snapshot)
{
	stack->pushPauseState(snapshot); 
}
State::Context State::getContext() const
{
	return context;
}
