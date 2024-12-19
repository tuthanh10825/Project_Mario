#pragma once
#include <sfml/System.hpp>
#include <sfml/Graphics.hpp>
#include <xutility>
#include "ResourceHolder.h"
#include "Player.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
class StateStack; 

class State {
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context {
		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
		MusicPlayer* musics; 
		SoundPlayer* sounds; 
		Context(sf::RenderWindow&, TextureHolder&, FontHolder&, Player&, MusicPlayer&, SoundPlayer&);
	};
	
public:
	State(StateStack& stack, Context context);
	virtual ~State() {}
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(States::ID stateId);
	void requestStackPop();
	void requestStateClear();
	void requestStackPushGame(Level level, Characters character);

	Context getContext() const;

private:
	StateStack* stack;
	Context context;
};