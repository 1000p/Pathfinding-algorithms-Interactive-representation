#include "InputManager.h"

#include "RenderManager.h"

#include <string>

InputManager::InputManager(NodesMap** map):mapR(map)
{
	int width;
	int height;
	inputWindowSize(width, height);
	RenderManager::createRendererAndWindow(width, height);
	inputMapSize(width, height);
	Node::initializeNodeTextures();
	*map = new NodesMap(width, height);

}

void InputManager::handleInputEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
		{
			terminateProgram("You exited the program.", 0);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			(*mapR)->handleInput(&e);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			(*mapR)->handleInput(&e);
			break;
		}
		default:
			break;
		}
	}
	
}

//Gets user input for the map size, recurse if there is negative width of height
void InputManager::inputMapSize(int& width, int& height)
{
	std::string input;
	int _width;
	int _height;
	std::cout << "Please enter map width: " << std::endl;
	getline(std::cin, input);
	if (!is_number(input))
	{
		std::cout << "You entered incorect width! Please try again." << std::endl;
		inputMapSize(width, height);
		return;
	}
	else
	{
		_width = std::stoi(input);
		width = _width;
	}

	if (width < 0)
	{
		std::cout << "You entered incorect width! Please try again." << std::endl;
		inputMapSize(width, height);
	}

	std::cout << "Please enter map height: " << std::endl;
	getline(std::cin, input);
	if (!is_number(input))
	{
		std::cout << "You entered incorect height! Please try again." << std::endl;
		inputMapSize(width, height);
		return;
	}
	else
	{
		_height = std::stoi(input);
		height = _height;
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

void InputManager::inputWindowSize(int& width, int& height)
{
	std::string input;
	int _width;
	int _height;
	std::cout << "Please enter window width: " << std::endl;
	getline(std::cin,input); 
	if (!is_number(input))
	{
		std::cout << "You entered incorect width! Please try again." << std::endl;
		inputWindowSize(width, height);
		return;
	}
	else
	{
		_width = std::stoi(input);
		width = _width;
	}

	if (width < 0)
	{
		std::cout << "You entered incorect width! Please try again." << std::endl;
		inputWindowSize(width, height);
	}
	
	std::cout << "Please enter window height: " << std::endl;
	getline(std::cin, input);
	if (!is_number(input))
	{
		std::cout << "You entered incorect height! Please try again." << std::endl;
		inputWindowSize(width, height);
		return;
	}
	else
	{
		_height = std::stoi(input);
		height = _height;
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

inline bool InputManager::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
