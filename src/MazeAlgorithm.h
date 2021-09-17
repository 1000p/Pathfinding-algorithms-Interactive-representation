#pragma once
#include "SDL.h"

class Node;
class NodesMap;
//Pure abstract base class for maze generating algorithms

class MazeAlgorithm
{
public:
	virtual ~MazeAlgorithm() = default;

	virtual void generateMaze(NodesMap* map, SDL_Renderer* renderer)  = 0;

};

