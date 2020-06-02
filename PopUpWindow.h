#pragma once
#include "ButtonComponent.h"

#include <vector>

//Used as a popup when pressing buttons 
class PopUpWindow
{
public:

    PopUpWindow(MainWindow* owner, Uint32 windowFlags);
    
    void handleEvent(SDL_Event* evt);

    void render();

    void close();

private:
    MainWindow* owner;
    SDL_Window* window;
    SDL_Renderer* renderer;
	std::vector<Component*> components;
    
};

