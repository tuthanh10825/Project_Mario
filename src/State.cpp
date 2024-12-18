#include "State.h"
#include "StateStack.h"
State::Context::Context(sf::RenderWindow& window, TextureHolder& textureHolder,
	FontHolder& fontHolder, Player& player, MusicPlayer& musics, SoundPlayer& sounds) :
	window(&window), textures(&textureHolder), fonts(&fontHolder), player(&player), musics(&musics), sounds(&sounds)
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
void State::requestStackPushGame(Level level, Characters character) {
	stack->pushGameState(level, character); 
}
State::Context State::getContext() const
{
	return context;
}
