#pragma once
#include "OrientationDefines.h"
#include "MazeAlgorithm.h"


class RecursiveDivision: public MazeAlgorithm
{
public:
	RecursiveDivision(int resolution) : resolution(resolution) {}

	virtual void generateMaze(NodesMap* map) override;

private:
	Orientation chooseOrientation(int width, int height);

	int resolution;
};

