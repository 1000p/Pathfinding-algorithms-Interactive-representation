#include "RenderManager.h"

SDL_Renderer* RenderManager::renderer = nullptr;
SDL_Window* RenderManager::window = nullptr;
int RenderManager::windowW = 0;
int RenderManager::windowH = 0;

void RenderManager::createRendererAndWindow(const int width,const int height)
{
	//Create window
	window = SDL_CreateWindow("Visualizer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 
		SDL_WINDOW_RESIZABLE
		| SDL_WINDOW_HIDDEN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED 
			| SDL_RENDERER_TARGETTEXTURE);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(renderer);
		}
	}

	windowW = width;
	windowH = height;
}
