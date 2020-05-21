#pragma once

#include "Globals.h"
#include "StateDefines.h"

#include <iostream>
#include <deque>

#include "SDL.h"
#include "SDL_image.h"

class NodesMap;
class InputManager;
class ResourceInitializer;

class Node
{
public:

	Node(NodeState state, int x, int y, NodesMap* owner)
		:texture(nullptr),owner(owner),state(state),previousState(state),memoryState(state),
		permanentState(state),x(x),y(y){
		changeState(state);
	}

	//static void initializeNodeTextures();

	void changeState(NodeState newState);

	void handleEvent (SDL_Event* evt);

private:

	SDL_Texture* texture;
	NodesMap* owner;
	NodeState state;
	NodeState memoryState;
	NodeState permanentState;
	NodeState previousState;

	int x;
	int y;
	
	static ResourceInitializer& resourceInit;
	static InputManager& inputManager;
	


	friend class RenderManager;
	friend class MainWindow;
};

