#include "Application.h"

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
	//	stateStack.registerState<GameState>(States::Game); 
	//  stateStack.registerState<PauseState>(States::Pause); 
}

void Application::run()
{
	while (window.isOpen()) {
		processInput();
		if (stateStack.isEmpty()) window.close(); 
		render();

	}
}

Application::Application() : window(sf::VideoMode::getDesktopMode(), "Super Mario", sf::Style::Close | sf::Style::Titlebar),
	textures(), fonts(), stateStack(State::Context(window, textures, fonts))
{
	window.setKeyRepeatEnabled(false);
	window.setSize(window.getSize()); 
	fonts.load(Fonts::PixeloidSansBold, "fonts/PixeloidSansBold.ttf"); 
	fonts.load(Fonts::PixeloidMono, "fonts/PixeloidMono.ttf");
	registerStates(); 
	stateStack.pushState(States::Menu);

}


