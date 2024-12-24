#include "Application.h"
#include <exception>
#include <iostream>
int main()
{
	try {
		Application game;
		game.run();
	}
	catch (std::exception& e) {
		std::cout << e.what(); 
	}
	return 0; 
}
