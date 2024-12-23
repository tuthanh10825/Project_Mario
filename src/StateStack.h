#pragma once
#include<sfml/System/NonCopyable.hpp>
#include<sfml/System/Time.hpp>
#include <functional>
#include "ID.h"
#include "State.h"
#include "GameState.h"
#include "DeathState.h"

class StateStack :private sf::NonCopyable {
public: 
	enum Action {
		Push, 
		Pop, 
		Clear,
	};
public:
	explicit StateStack(State::Context context); 

	template<typename T> 
	void registerState(States::ID stateID); 

	void update(sf::Time dt); 
	void draw(); 
	void handleEvent(const sf::Event& event); 

	void pushState(States::ID stateID);
	void pushGameState(Level level, Characters character); 
	void pushDeathState(Level level, Characters character); 
	void popState();
	void clearStates(); 
	bool isEmpty() const; 
	
private: 
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges(); 

private: 
	struct PendingChange {
		explicit PendingChange
		(Action action
		,States::ID stateID = States::None
		,Level level = Level::None
		,Characters character = Characters::CharNone); 

		Action action;
		States::ID stateID;
		Level level; 
		Characters character;
	};
private: 
	std::vector<State::Ptr> stack; 
	std::vector<PendingChange> pendingList; 

	State::Context context; 
	std::map<States::ID, std::function<State::Ptr()>> factories;

};

template<typename T>
void StateStack::registerState(States::ID stateID)
{
	factories[stateID] = [this]() {
		return State::Ptr(new T(*this, context)); 
		};
}
