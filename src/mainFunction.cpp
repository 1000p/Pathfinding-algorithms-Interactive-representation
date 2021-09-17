#include <cstdlib>
#include <time.h>

#include "InputManager.h"
#include "ResourceInitializer.h"

#include "MainWindow.h"
#include "RenderManager.h"


int main(int argc, char* argv[])
{
	//seed the rand function
	std::srand(time(NULL));

	MainWindow* mainWindow = new MainWindow();
	NodesMap* map = mainWindow->getMap();
	InputManager& input = InputManager::getInstance();

	//If there is an Error 
	std::cout << SDL_GetError();
	
	while (true)
	{
		input.handleInputEvents();
		mainWindow->render();
	}
	return 0;
}