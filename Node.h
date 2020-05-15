#pragma once

#include "Globals.h"
#include "StateDefines.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

class NodesMap;
class InputManager;
class ResourceInitializer;

class Node
{
public:

	Node(NodeState state, int x, int y, NodesMap* owner)
		:texture(nullptr),owner(owner),state(state), x(x),y(y){
		changeState(state);
	}

	//static void initializeNodeTextures();

	void changeState(NodeState newState);

	void handleEvent (SDL_Event* evt);

private:
	SDL_Texture* texture;
	NodesMap* owner;
	NodeState state;
	int x;
	int y;
	
	static ResourceInitializer& resourceInit;
	static InputManager& inputManager;
	
	/*
	static SDL_Texture* openT;
	static SDL_Texture* closedT;
	static SDL_Texture* startT;
	static SDL_Texture* endT;
	static SDL_Texture* pathT;
	static SDL_Texture* obstacleT;
	static SDL_Texture* whiteT;
	static SDL_Texture* hoverT;
	*/

	friend class RenderManager;
	friend class MainWindow;
};

