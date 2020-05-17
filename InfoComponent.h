#pragma once
#include "Component.h"

#include "RenderManager.h"

#include "SDL.h"
#include "SDL_ttf.h"

#include <vector>


class InfoComponent: public Component
{
public:

	InfoComponent(MainWindow* owner) : Component(), owner(owner)
	{
		init();
	}

	SDL_Rect getGeometry() const
	{
		return geometry;
	}

	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) override
	{
		SDL_SetRenderTarget(renderer, target);
		SDL_RenderCopy(renderer, background, NULL,&geometry );
		for (auto elem : elements)
		{
			elem->render(renderer, target);
		}
	}

	SDL_Texture* getTexture()
	{
		return background;
	}

	bool is_inside(int x, int y)
	{
		if (x >= geometry.x && x <= geometry.x + geometry.w)
		{
			if (y >= geometry.y && y <= geometry.y+geometry.h)
			{
				return true;
			}
		}
		return false;
	}

	// Inherited via Component
	virtual void handleEvent(SDL_Event* evt) override;

private:

	void init();

	std::vector<Component*> elements;
	MainWindow* owner;
	SDL_Texture* background;
	TTF_Font* font;
	SDL_Rect geometry;
	
};

