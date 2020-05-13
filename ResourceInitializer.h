#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

#include "StateDefines.h"

#include <iostream>

class ResourceInitializer
{
public:

	static ResourceInitializer& getInstance()
	{
		static ResourceInitializer instance;
		return instance;
	}

	void init();

	SDL_Texture* getTexture(NodeState type) const;

	TTF_Font* getFont() const;

private:
	ResourceInitializer() = default;


	ResourceInitializer(ResourceInitializer& const) = delete;
	void operator = (ResourceInitializer& const) = delete;

	void initializeNodeTextures();
	
	void initializeFont();
	

	static SDL_Texture* openT;
	static SDL_Texture* closedT;
	static SDL_Texture* startT;
	static SDL_Texture* endT;
	static SDL_Texture* pathT;
	static SDL_Texture* obstacleT;
	static SDL_Texture* whiteT;
	static SDL_Texture* hoverT;

	static TTF_Font* font;
};

