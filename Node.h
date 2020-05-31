#pragma once

//#include "NodesMap.h"
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

	Node(NodeState state, int y, int x, NodesMap* owner)
		:texture(nullptr),owner(owner),state(state),previousState(state),memoryState(state),
		permanentState(state),pathParrent(nullptr),x(x),y(y), Gcost(0), Hcost(0){
		changeState(state);
	}

	//static void initializeNodeTextures();

	void changeState(NodeState newState);

	void handleEvent (SDL_Event* evt);

	void handleMapPhase(NodeState tileState);

	int getX() const
	{
		return x;
	}

	int getY() const
	{
		return y;
	}

	int Fcost()
	{
		return Gcost + Hcost;
	}

private:

	SDL_Texture* texture;
	NodesMap* owner;
	NodeState state;
	NodeState memoryState;
	NodeState permanentState;
	NodeState previousState;

	Node* pathParrent;

	int x;
	int y;

	int Gcost;
	int Hcost;
	
	static ResourceInitializer& resourceInit;
	static InputManager& inputManager;
	
	friend class NodesMap;
	friend class AStarPathfinder;
	friend class RenderManager;
	friend class MainWindow;
};

