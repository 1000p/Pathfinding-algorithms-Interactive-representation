#pragma once

#include "Globals.h"
#include "StateDefines.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

class NodesMap;

class Node
{
public:

	Node(NodeState state, int x, int y, NodesMap* owner)
		:texture(nullptr),owner(owner),state(state), x(x),y(y){
		changeState(state);
	}

	static void initializeNodeTextures();

	void changeState(NodeState newState)
	{
		state = newState;

		switch (state)
		{
			case NodeState::CLOSED:
			{
				texture = closedT;
				break;
			}
			case NodeState::OPEN:
			{
				texture = openT;
				break;
			}
			case NodeState::END:
			{
				texture = endT;
				break;
			}
			case NodeState::START:
			{
				texture = startT;
				break;
			}
			case NodeState::OBSTACLE:
			{
				texture = obstacleT;
				break;
			}
			case NodeState::WHITE:
			{
				texture = whiteT;
				break;
			}
			case NodeState::PATH:
			{
				texture = pathT;
				break;
			}
			case NodeState::HOVER:
			{
				texture = hoverT;
				break;
			}
			default:
			{
				//TODO: ADD TERMINATE PROGRAM FUNCTION RETURNING ERROR MSG
				texture = nullptr;
				break;
			}		
		}
	}

	void handleEvent(SDL_Event* evt);

private:
	SDL_Texture* texture;
	NodesMap* owner;
	NodeState state;
	int x;
	int y;
	
	static SDL_Texture* openT;
	static SDL_Texture* closedT;
	static SDL_Texture* startT;
	static SDL_Texture* endT;
	static SDL_Texture* pathT;
	static SDL_Texture* obstacleT;
	static SDL_Texture* whiteT;
	static SDL_Texture* hoverT;

	friend class RenderManager;
};

