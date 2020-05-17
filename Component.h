#pragma once
#include "SDL.h"

class Component
{	
public:
	virtual ~Component() = default;

	virtual void handleEvent(SDL_Event* evt) = 0;

	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) = 0;
	
};

