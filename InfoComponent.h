#pragma once
#include "Component.h"
#include "SDL.h"
#include "SDL_ttf.h"

#include <vector>


class InfoComponent: public Component
{
public:

	// Inherited via Component
	virtual void handleEvent() override;

private:

	void init();

	
	TTF_Font* font;
	SDL_Rect geometry;
	
};

