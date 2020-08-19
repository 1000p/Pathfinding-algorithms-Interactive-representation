#include "RecursiveDivision.h"

#include "NodesMap.h"
#include "Node.h"
#include <stack>

void RecursiveDivision::generateMaze(NodesMap* map)
{
	int width = map->getWidth();
	int height = map->getHeight();

	int mapWidth = width;
	int mapHeight = height;


	int x = 0, y = 0;
	int wX = 0, wY = 0; //Where the wall will be drawn from.
	int wallLenght;

	int pX = 0, pY = 0; //Where the passage should be.

	std::stack<SDL_Rect> tail;

	bool wallOrientationHorizontal;

	while (true)
	{
		Orientation wallOrientation = chooseOrientation(width, height);
		wallOrientationHorizontal = wallOrientation == Orientation::Horizontal ? true : false;
		wX = x + (wallOrientationHorizontal ? 0 : rand() % width );
		wY = y + (wallOrientationHorizontal ? rand() % height : 0);

		pX = wX + (wallOrientationHorizontal ? rand() % width : 0);
		pY = wY + (wallOrientationHorizontal ? 0 : rand() % height);

		wallLenght = wallOrientationHorizontal ? width : height;

		if (width < resolution || height < resolution) // That is the stack use flag
		{
			if (tail.empty())
			{
				return;
			}
			//polzvai rect ot stack-a
			x = tail.top().x; y = tail.top().y; width = tail.top().w; height = tail.top().h;
			tail.pop();
			continue;
		}
		else
		{
			//polzvai current rect i slagai po malkiq na stack-a
			switch (wallOrientation)
			{
				case Orientation::Horizontal:
				{
					if ((height - (height - wY)) >= (height - wY) ) // Upper rectang is larger
					{
						tail.push({ x,wY+1,wallLenght,height - (height - wY) });						
						height = height - (height - wY);
					}
					else //Upper rectang is smaller
					{
						tail.push({ x,y,wallLenght,height - (height - wY) });
						height = (height - wY);
					}
					//Drawing of the wall --> Can be extracted to a function
					for (int i = 0; i < wallLenght; ++i)
					{
						map->getNode(wX + i, wY)->hardChangeState(NodeState::OBSTACLE);
					}
					width = wallLenght;

					break;
				}
				//TODO: Use abs(xx) to fix checking & generation of width and height 
				case Orientation::Vertical:
				{
					if ((width - (width - wX)) >= (width - wX)-1 ) // Left rectang is larger 
					{
						tail.push({ wX + 1,y, (width - wX)-1 ,wallLenght });					
						width = width - (width - wX);
					}
					else											//Left rectang is smaller
					{
						tail.push({ x,y, width - (width - wX) ,wallLenght });		/*TESTED!!!!!!!!!!!!!*/
						width = (width - wX)-1;
					}
																	//Drawing of the wall --> Can be extracted to a function
					for (int i = 0; i < wallLenght; ++i)
					{
						map->getNode(wX, wY + i)->hardChangeState(NodeState::OBSTACLE);
					}

					map->getNode(pX, pY)->hardChangeState(NodeState::WHITE);
					
					if ( wallLenght -(wallLenght-pY)  <= wallLenght - pY-1) //Upper rect ABOVE PASSAGE split is smaller
					{
						tail.push({ pX+1,(pY == 0 ? 0 : pY-1), width, wallLenght - (wallLenght - pY) });	/*TESTED WITH VERTICAL RIGHT BIGGER*/
						height = wallLenght - pY-1;															/*TESTED WITH VERTICAL LEFT BIGGER*/
					}
					else												  //Upper rect ABOVE PASSAGE split is bigger
					{
						tail.push({pX+1,(pY >= mapHeight ? mapHeight : pY+1), width, wallLenght - pY - 1 }); /*TESTED WITH VERTICAL RIGHT BIGGER*/
						height = wallLenght - (wallLenght - pY);											 /*TESTED WITH VERTICAL LEFT BIGGER*/
					}

					
					break;
				}
				default:
					break;
			}
			
			x = wX; y = wY;
		}
				
	}
	
}


Orientation RecursiveDivision::chooseOrientation(int width, int height)
{
	Orientation toReturn = width < height ? Orientation::Horizontal : Orientation::Vertical;

	return toReturn;
}
