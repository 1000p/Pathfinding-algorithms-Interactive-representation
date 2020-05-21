#pragma once

#include "MainWindow.h"
#include "RenderManager.h"
#include "Component.h"
#include "ButtonDefines.h"

#include "SDL.h"
#include "SDL_ttf.h"

#include <utility>

class ButtonComponent: public Component
{
public:
	ButtonComponent(std::pair <SDL_Rect, SDL_Texture*> texture,
		std::pair <SDL_Rect, SDL_Texture*> text, ButtonType type,MainWindow* owner)
		: Component(), type(type),pressed(false),owner(owner)
	{
		geometry.x = texture.first.x;
		geometry.y = texture.first.y;
		geometry.w = texture.first.w + text.first.w +5;
		geometry.h = texture.first.h;

		pressedGeometry.w =geometry.w - (geometry.w * 0.05);
		pressedGeometry.h = geometry.h - (geometry.h * 0.05);
		pressedGeometry.x = geometry.x + ((geometry.w - pressedGeometry.w) / 2);
		pressedGeometry.y = geometry.y + ((geometry.y - pressedGeometry.y) / 2);

		SDL_Renderer* renderer = RenderManager::getRenderer();
		Uint32 format;
		SDL_QueryTexture(texture.second, &format, NULL, NULL, NULL);

		this->texture = SDL_CreateTexture(renderer, format, 
			SDL_TEXTUREACCESS_TARGET,
			geometry.w, geometry.h);

		texture.first.x = 0;
		texture.first.y = 0;
		text.first.x = texture.first.x + texture.first.w + 5;
		text.first.y = 0;

		SDL_Texture* target = SDL_GetRenderTarget(renderer);
		SDL_SetRenderTarget(renderer, this->texture);
		SDL_RenderCopy(renderer, texture.second, NULL, &texture.first);
		SDL_RenderCopy(renderer, text.second, NULL, &text.first);
		SDL_SetRenderTarget(renderer, target);
	}

	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) override
	{
		SDL_SetRenderTarget(renderer, target);
		if (pressed)
		{
			SDL_RenderCopy(renderer, texture, NULL, &pressedGeometry);
			return;
		}	
		SDL_RenderCopy(renderer, texture, NULL, &geometry);
	}

	// Inherited via Component
	virtual void handleEvent(SDL_Event* evt) override;

private:

	bool is_inside(int x, int y)
	{
		if (x >= geometry.x && x <= geometry.x + geometry.w)
		{
			if (y >= geometry.y && y <= geometry.y + geometry.h)
			{
				return true;
			}
		}
		return false;
	}

	bool pressed;
	MainWindow* owner;
	SDL_Texture* texture;
	ButtonType type;
	SDL_Rect geometry;
	SDL_Rect pressedGeometry;
};

