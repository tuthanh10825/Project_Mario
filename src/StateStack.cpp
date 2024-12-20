#include "StateStack.h"

StateStack::PendingChange::PendingChange(StateStack::Action action, States::ID stateID, Level level, Characters character) : action(action), stateID(stateID), level(level), character(character) {}
StateStack::StateStack(State::Context context) : context(context) {}
class Character; 
enum Character::Type; 
 
void StateStack::update(sf::Time dt)
{
	for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
		if (!(*it)->update(dt))
			break; 
	}
	applyPendingChanges();
}
void StateStack::draw()
{
	for (auto &state : stack) {
		state->draw(); 
	}
}
void StateStack::handleEvent(const sf::Event& event)
{
	for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
		if (!(*it)->handleEvent(event)) break; 
	}

	applyPendingChanges(); 
}
void StateStack::pushState(States::ID stateID)
{
	this->pendingList.push_back(PendingChange(Action::Push, stateID)); 
}
void StateStack::pushGameState(Level level, Characters character) {
	this->pendingList.push_back(PendingChange(Action::Push, States::Game, level, character));
}

void StateStack::popState()
{
	this->pendingList.push_back(PendingChange(Action::Pop)); 
}

void StateStack::clearStates()
{
	this->pendingList.push_back(PendingChange(Action::Clear));
}


bool StateStack::isEmpty() const
{
	return stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID) {
	auto found = factories.find(stateID); 
	assert(found != factories.end()); 

	return found->second(); 
	
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : pendingList) {
		switch (change.action) {
		case Push: 
			stack.push_back(createState(change.stateID));
			if (change.stateID == States::Game) {
				assert(change.character != Characters::CharNone);
				switch (change.character) {
				case Characters::Character1: 
						static_cast<GameState&>(*stack.back().get()).setLevel(change.level, Character::Character1);
						break; 
				case Characters::Character2: 
						static_cast<GameState&>(*stack.back().get()).setLevel(change.level, Character::Character2);
						break; 
				default: 
					throw; 
				}
				
			}
			break; 
		case Pop: 
			stack.pop_back(); 
			break; 
		case Clear: 
			stack.clear(); 
			break; 
		}
	}
	pendingList.clear(); 
	return; 
}

