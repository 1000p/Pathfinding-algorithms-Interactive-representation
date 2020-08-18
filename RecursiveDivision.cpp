#include "RecursiveDivision.h"

#include "NodesMap.h"
#include <stack>

void RecursiveDivision::generateMaze(NodesMap* map)
{
	int width = map->getWidth();
	int height = map->getHeight();

	int mapWidth = width;
	int mapHeight = height;

	int modifier;

	int x = 0, y = 0;
	int wX = 0, wY = 0; //Where the wall will be drawn from.
	int wallLenght;

	int pX = 0, pY = 0; //Where the passage should be.

	std::stack<SDL_Rect> tail;

	bool wallOrientationHorizontal;
	Orientation wallOrientation = chooseOrientation(width, height);

	while (true)
	{
		wallOrientationHorizontal = wallOrientation == Orientation::Horizontal ? true : false;
		wX = x + (wallOrientationHorizontal ? 0 : rand() % width - 1);
		wY = y + (wallOrientationHorizontal ? rand() % height - 1 : 0);

		pX = wX + (wallOrientationHorizontal ? rand() % width : 0);
		pY = wY + (wallOrientationHorizontal ? 0 : rand() % height);

		wallLenght = wallOrientationHorizontal ? width : height;

		if (width < resolution || height < resolution) // That is the stack use flag
		{
			//polzvai rect ot stack-a
			x = tail.top().x; y = tail.top().y; width = tail.top().w; height = tail.top().h;
			continue;
		}
		else
		{
			if (tail.empty())
			{
				return;
			}
			//polzvai current rect i slagai po malkiq na stack-a
			switch (wallOrientation)
			{
				case Orientation::Horizontal:
				{
					tail.push({ wX,wY - 1,wallLenght,wY - 1 });
					break;
				}
				case Orientation::Vertical:
				{
					tail.push({ wX - 1,wY ,wX - 1,wY });//TODO
					break;
				}
				default:
					break;
				}
		}	
		//Drawing of the wall can be extracted to a function

	}
	
}


Orientation RecursiveDivision::chooseOrientation(int width, int height)
{
	Orientation toReturn = width < height ? Orientation::Horizontal : Orientation::Vertical;

	return toReturn;
}
