#include "Globals.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "Node.h"

int main(int argc, char* argv[])
{
	SDL_ShowWindow(RenderManager::getWindow());
	//Initialize the user input phace
	// - Size of the coordinate system
	// - Start and End points
	// - Add obsticles 
	// Keep it simple for now, just use the console for input

	NodesMap* map = nullptr;

	InputManager input(&map);	
	std::cout << SDL_GetError();
	RenderManager::InitialMapRender(map);

	while (true)
	{
		input.handleInputEvents();
		RenderManager::renderMap(map);
	}
	return 0;
}