#include "State.h"
#include "StateStack.h"
State::Context::Context(sf::RenderWindow& window, TextureHolder& textureHolder,
	FontHolder& fontHolder, Player& player) :
	window(&window), textures(&textureHolder), fonts(&fontHolder), player(&player) {

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
void State::requestStackPushGame(Level level) {
	stack->pushGameState(level); 
}
State::Context State::getContext() const
{
	return context;
}
