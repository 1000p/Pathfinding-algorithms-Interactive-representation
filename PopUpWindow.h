#pragma once
#include "ButtonComponent.h"
#include "WindowType.h"

#include <vector>


//Used as a popup when pressing buttons 
class PopUpWindow
{
public:

    PopUpWindow(MainWindow* owner, Uint32 windowFlags, WindowType type);
    
    void handleEvent(SDL_Event* evt);

    void render();

    void close();

private:

    void createMazeAlgorithmPopUpWindow();
    void createPathAlgorithmPopUpWindow();

    MainWindow* owner;
    SDL_Window* window;
    SDL_Renderer* renderer;
	std::vector<Component*> components;
    
};

