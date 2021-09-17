#pragma once

#include "StateDefines.h"

#include <iostream>
#include <deque>

#include "SDL.h"
#include "SDL_image.h"


class InputManager;
class ResourceInitializer;
class RenderManager;
class NodesMap;

class Node
{
public:

	Node(NodeState state, int y, int x, NodesMap* owner);

	void changeState(NodeState newState);

	void hardChangeState(NodeState newState);

	void handleEvent (SDL_Event* evt);

	void handleMapPhase(NodeState tileState);

	int getX() const;

	int getY() const;

	int Fcost();

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

