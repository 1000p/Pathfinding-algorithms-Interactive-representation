#pragma once
#include "SDL.h"

class Component
{	
public:
	virtual ~Component() = default;

	virtual void handleEvent(SDL_Event* evt) = 0;

	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) = 0;

	virtual SDL_Rect getGeometry() const = 0;

	virtual void destroy() = 0;
	
};

