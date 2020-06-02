#pragma once

#include <iostream>
#include "SDL.h"

class RenderManager
{
public:
    RenderManager()
    {} 
 
    static SDL_Window* getWindow() 
    {
        return window;
    }

    static SDL_Renderer* getRenderer()
    {
        return renderer;
    }

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static int windowW;
    static int windowH;
    static void createRendererAndWindow(const int width, const int height);

    friend class InputManager;
};

