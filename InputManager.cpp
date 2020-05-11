#include "InputManager.h"

#include "RenderManager.h"

InputManager::InputManager(NodesMap** map)
{
	int width;
	int height;
	inputWindowSize(width, height);
	RenderManager::createRendererAndWindow(width, height);
	inputMapSize(width, height);
	Node::initializeNodeTextures();
	*map = new NodesMap(width, height);

}
