#pragma once
#include "OrientationDefines.h"

class NodesMap;


class RecursiveDivision
{
public:
	RecursiveDivision(int resolution) : resolution(resolution) {}

	void generateMaze(NodesMap* map);

private:

	void drawWall(NodesMap* map);
	Orientation chooseOrientation(int width, int height);

	int resolution;
};

