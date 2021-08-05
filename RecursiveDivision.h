#pragma once
#include "OrientationDefines.h"
#include "MazeAlgorithm.h"


class RecursiveDivision: public MazeAlgorithm
{
public:
	RecursiveDivision(int resolution) : resolution(resolution) {}

	virtual void generateMaze(NodesMap* map, SDL_Renderer* renderer) override;
	
private:
	void divide(NodesMap* map, int x, int y, int width, int height, Orientation orientation, SDL_Renderer* renderer);
	Orientation chooseOrientation(int width, int height);

	int resolution;
};

