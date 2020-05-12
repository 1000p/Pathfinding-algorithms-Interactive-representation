#pragma once

#include "NodesMap.h"
#include <cctype>

class InputManager
{
public:

	InputManager(NodesMap** map);

	void handleInputEvents();

private:

	//Gets user input for the map size, recurse if there is negative width of height
	void inputMapSize(int& width, int& height);

	//Gets user input for the window size, recurse if there is negative width of height
	void inputWindowSize(int& width, int& height);

	bool is_number(const std::string& s);	

	//Terminates the program with a message and exit code
	void terminateProgram(const std::string& message, int code)
	{
		std::cout <<"\n"<< message << std::endl;
		exit(code);
	}

	NodesMap** mapR;
	std::vector<Node*> obstacles;
};

