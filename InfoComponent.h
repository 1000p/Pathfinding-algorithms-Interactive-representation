#pragma once
#include "Component.h"

#include "RenderManager.h"

#include "SDL.h"
#include "SDL_ttf.h"

#include <vector>


class InfoComponent: public Component
{
public:

	InfoComponent() : Component() 
	{
		init();
	}

	SDL_Rect getGeometry() const
	{
		return geometry;
	}

	void render(SDL_Renderer* renderer, SDL_Texture* target)
	{
		SDL_SetRenderTarget(renderer, target);
		SDL_RenderCopy(renderer, background, NULL,&geometry );
	}

	SDL_Texture* getTexture()
	{
		//SDL_RenderCopy(RenderManager::getRenderer(), background, NULL, NULL);
		//SDL_RenderPresent(RenderManager::getRenderer());
		return background;
	}

	// Inherited via Component
	virtual void handleEvent() override;

private:

	void init();

	SDL_Texture* background;
	TTF_Font* font;
	SDL_Rect geometry;
	
};

