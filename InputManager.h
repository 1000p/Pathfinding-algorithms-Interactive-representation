#pragma once

#include "NodesMap.h"


class InputManager
{
public:

	InputManager(NodesMap** map);

private:

	//Gets user input for the map size, recurse if there is negative width of height
	void inputMapSize(int& width, int& height)
	{
		std::cout << "Please enter map width: " << std::endl;
		std::cin >> width;
		std::cout << "Please enter map height: "<< std::endl;
		std::cin >> height;
		if (width < 0)
		{
			std::cout << "You entered negative width! Please try again." << std::endl;
			inputMapSize(width, height);
		}
		if (height < 0)
		{
			std::cout << "You entered negative height! Please try again." << std::endl;
			inputMapSize(width, height);
		}
		if (width == 0 && height == 0)
		{
			std::cout << "You entered both width and height to be zero! Please try again." << std::endl;
			inputMapSize(width, height);
		}
	}

	void inputWindowSize(int& width, int& height)
	{
		std::cout << "Please enter window width: " << std::endl;
		std::cin >> width;
		std::cout << "Please enter window height: " << std::endl;
		std::cin >> height;
		if (width < 0)
		{
			std::cout << "You entered negative width! Please try again." << std::endl;
			inputWindowSize(width, height);
		}
		if (height < 0)
		{
			std::cout << "You entered negative height! Please try again." << std::endl;
			inputWindowSize(width, height);
		}
		if (width == 0 && height == 0)
		{
			std::cout << "You entered both width and height to be zero! Please try again." << std::endl;
			inputWindowSize(width, height);
		}

		//To avoid odd resolutions
		if (width % 2 != 0)
		{
			width -= 1;
		}
		if (height % 2 != 0)
		{
			height -= 1;
		}
	}

	std::vector<Node*> obstacles;
};

