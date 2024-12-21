#include "Application.h"
int main()
{
	Application *game = Application::getInstance(); 
	game->run(); 
	return 0; 
}
