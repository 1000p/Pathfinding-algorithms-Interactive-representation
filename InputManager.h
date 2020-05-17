#pragma once

#include "NodesMap.h"

#include <cctype>

class MainWindow;

class InputManager
{
public:

	static InputManager& getInstance()
	{
		static InputManager instance;
		return instance;
	}

	void init(NodesMap** map, MainWindow* window);

	void handleInputEvents();

	SDL_EventType getMouseState() const
	{
		return mouseState;
	}

private:
	InputManager() : mapR(nullptr), mouseState(SDL_MOUSEBUTTONUP) {}
	InputManager(InputManager const&) = delete;
	void operator = (InputManager const&) = delete;

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

	MainWindow* mainWindow;
	NodesMap** mapR;
	std::vector<Node*> obstacles;
	SDL_EventType mouseState;

	
};

