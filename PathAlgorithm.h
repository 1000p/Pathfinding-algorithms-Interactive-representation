#pragma once

#include "SDL.h"

class Node;
//Pure abstract base class for path finding algorithms
class PathAlgorithm
{
public:
	virtual ~PathAlgorithm() = default;

	virtual void findPath(Node* start, Node* target, bool delay,
		SDL_Renderer* renderer, SDL_Texture* renderTarget) = 0;
	
};

