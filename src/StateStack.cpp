#include "StateStack.h"
StateStack::PendingChange::PendingChange(StateStack::Action action, States::ID stateID) : action(action), stateID(stateID) {}
StateStack::StateStack(State::Context context) : context(context) {}
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

