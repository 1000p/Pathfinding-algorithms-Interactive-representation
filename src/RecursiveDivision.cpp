#include "RecursiveDivision.h"

#include "NodesMap.h"
#include "Node.h"
#include <stack>

void RecursiveDivision::generateMaze(NodesMap* map,SDL_Renderer* renderer)
{
	int width = map->getWidth();
	int height = map->getHeight();
	divide(map,0, 0, width, height, chooseOrientation(width, height),renderer);
}

void RecursiveDivision::divide(NodesMap* map, int x, int y, int width, int height, Orientation orientation, SDL_Renderer* renderer)
{
	if (width < resolution || height < resolution)
	{
		return;
	}

	bool wallIsHorizontal = orientation == Orientation::Horizontal;
	const int truewidth = (width - 1) / 2;
	const int trueheight = (height - 1) / 2;
	//Where the wall is
	int wX = x + (wallIsHorizontal ? 0 : 2 * (rand() % (truewidth)) + 1);
	int wY = y + (wallIsHorizontal ? 2 * (rand() % (trueheight)) + 1 : 0);
	//Where the passage is
	int pX = wX + (wallIsHorizontal ? 2 * (rand() % (truewidth)) : 0);
	int pY = wY + (wallIsHorizontal ? 0 : 2 * (rand() % (trueheight)));
	//How long is the wall
	int wallLenght = (wallIsHorizontal ? width : height);
	//On whitch axis will the wall be drawn
	int dX = wallIsHorizontal ? 1 : 0;
	int dY = wallIsHorizontal ? 0 : 1;
	//Draw the wall
	for (int i = 0; i < wallLenght; ++i)
	{
		if (wX != pX || wY != pY)
		{
			map->getNode(wX, wY)->hardChangeState(NodeState::OBSTACLE);
		}
		
		wX += dX;
		wY += dY;
	}
	//Render the current state
	//map->render(renderer, nullptr);
	//SDL_RenderPresent(renderer);	
	int nX = x; int nY = y;
	int w = wallIsHorizontal ? width : (wX - x);
	int h = wallIsHorizontal ? (wY - y ) : height;
	divide(map, nX, nY, w, h, chooseOrientation(w, h), renderer);

	nX = wallIsHorizontal ? x : (wX + 1);
	nY = wallIsHorizontal ? (wY + 1) : y;
	w = wallIsHorizontal ? width : (x + width - wX -1);
	h = wallIsHorizontal ? (y + height - wY-1 ) : height;
	divide(map, nX, nY, w, h, chooseOrientation(w, h),renderer);
}

Orientation RecursiveDivision::chooseOrientation(int width, int height)
{
	if (width < height)
	{
		return Orientation::Horizontal;
	}
	else if (width > height)
	{
		return Orientation::Vertical;
	}
	{
		Orientation toReturn;
		rand() % 2 == 0 ? toReturn= Orientation::Horizontal : toReturn = Orientation::Vertical;
		return toReturn;
	}	
}
