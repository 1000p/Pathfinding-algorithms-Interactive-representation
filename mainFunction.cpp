#include "InputManager.h"
#include "ResourceInitializer.h"
#include "MainWindow.h"

#include "Globals.h"

#include "RenderManager.h"
//#include "Node.h"

int main(int argc, char* argv[])
{
	/*
	InputManager& input = InputManager::getInstance();
	NodesMap* map = nullptr;
	input.init(&map);
	SDL_ShowWindow(RenderManager::getWindow());
	*/
	//Initialize the user input phace
	// - Size of the coordinate system
	// - Start and End points
	// - Add obsticles 
	// Keep it simple for now, just use the console for input

	
	MainWindow* mainWindow = new MainWindow();
	NodesMap* map = mainWindow->getMap();
	InputManager& input = InputManager::getInstance();

	//RenderManager::InitialMapRender(map);
	
	std::cout << SDL_GetError();
	

	while (true)
	{
		input.handleInputEvents();
		mainWindow->render();
	}
	return 0;
}