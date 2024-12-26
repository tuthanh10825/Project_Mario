#include "StateStack.h"

StateStack::PendingChange::PendingChange(StateStack::Action action, States::ID stateID, World::Snapshot snapshot) : action(action), stateID(stateID), snapshot(snapshot){}
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
void StateStack::pushGameState(World::Snapshot snapshot) {
	this->pendingList.push_back(PendingChange(Action::Push, States::Game, snapshot));
}

void StateStack::pushDeathState(World::Snapshot snapshot)
{
	this->pendingList.push_back(PendingChange(Action::Push, States::Death, snapshot)); 
}

void StateStack::pushPauseState(World::Snapshot snapshot)
{
	this->pendingList.push_back(PendingChange(Action::Push, States::Pause, snapshot)); 
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
				static_cast<GameState&>(*stack.back().get()).applySnapshot(change.snapshot);
			}
			else if (change.stateID == States::Death) {
				static_cast<DeathState&>(*stack.back().get()).applySnapshot(change.snapshot); 
			}
			else if (change.stateID == States::Pause) {
				static_cast<PauseState&>(*stack.back().get()).applySnapshot(change.snapshot); 
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

