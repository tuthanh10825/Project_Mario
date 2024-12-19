#include "Application.h"

const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);
void Application::processInput()
{
	sf::Event event; 
	while (window.pollEvent(event)) {
		stateStack.handleEvent(event); 
		if (event.type == sf::Event::Closed) {
			window.close(); 
		}
	}
}

void Application::update(sf::Time dt)
{
	stateStack.update(dt);
}

void Application::render()
{
	window.clear(); 
	stateStack.draw(); 

	window.display(); 
}

void Application::registerStates()
{
	stateStack.registerState<MenuState>(States::Menu); 
	stateStack.registerState<GameState>(States::Game); 
	stateStack.registerState<PauseState>(States::Pause); 
	stateStack.registerState<LevelSelectState>(States::LevelSelect);
	stateStack.registerState<DeathState>(States::Death);
}

void Application::run()
{
	sf::Clock clock; 
	sf::Time timeSinceLastUpdate = sf::Time::Zero; 
	while (window.isOpen()) {
		processInput();
		timeSinceLastUpdate += clock.restart(); 
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
			if (stateStack.isEmpty())
				window.close();
			render();
		}

	}
}

Application::Application() : window(sf::VideoMode(1000, 800), "Super Mario", sf::Style::Close | sf::Style::Titlebar),
	textures(), fonts(), player(), musics(), sounds(), 
	stateStack(State::Context(window, textures, fonts, player, musics, sounds))
{
	//window.setKeyRepeatEnabled(false);
	window.setSize(window.getSize()); 

	fonts.load(Fonts::PixeloidSansBold, "fonts/PixeloidSansBold.ttf"); 
	fonts.load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf");
	registerStates(); 
	stateStack.pushState(States::Menu);
	musics.play(Music::MenuTheme);
}

Application::~Application()
{
	musics.stop();
}


