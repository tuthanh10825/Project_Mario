#include "State.h"
#include "StateStack.h"
State::Context::Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder) :
	window(&window), textures(&textureHolder), fonts(&fontHolder) {

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

State::Context State::getContext() const
{
	return context;
}
