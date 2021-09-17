#include "ButtonComponent.h"

#include "MainWindow.h"

ButtonComponent::ButtonComponent(std::pair<SDL_Rect, SDL_Texture*> texture, std::pair<SDL_Rect, SDL_Texture*> text, ButtonType type, MainWindow* owner, SDL_Renderer* renderer)
	: Component(), type(type), pressed(false), owner(owner)
{
	int gapDistance;
	//To the right of the button texture
	if (texture.first.x <= text.first.x)
	{
		gapDistance = text.first.x - (texture.first.x + texture.first.w);
		geometry.x = texture.first.x;
		texture.first.x = 0;
		text.first.x = texture.first.x + texture.first.w + gapDistance;
	}
	//To the left of the button texture
	else //if (texture.first.x > text.first.x)
	{
		gapDistance = texture.first.x - (text.first.x + text.first.w);
		geometry.x = text.first.x;
		text.first.x = 0;
		texture.first.x = text.first.x + text.first.w + gapDistance;
	}

	//If text its centered and smaller
	if (text.first.x + text.first.w <=
		texture.first.x + texture.first.w)
	{
		geometry.w = texture.first.w;
	}
	else //Use the gapDistance to find final width
	{
		geometry.w = (text.first.w + texture.first.w) + gapDistance;
	}


	//If text its centered and smaller
	if (texture.first.y <= text.first.y)
	{
		gapDistance = text.first.y - (texture.first.y + texture.first.h);
		geometry.y = texture.first.y;
		texture.first.y = 0;
		text.first.y = texture.first.y + texture.first.h + gapDistance;
	}
	//Above the button texture
	else if (texture.first.y > text.first.y)
	{
		gapDistance = texture.first.y - (text.first.y + text.first.h);
		geometry.y = text.first.y;
		text.first.y = 0;
		texture.first.y = text.first.y + text.first.h + gapDistance;
	}

	//If its in or below/above and smaller
	if (text.first.y + text.first.h <=
		texture.first.y + texture.first.h)
	{
		geometry.h = texture.first.h;
	}
	else //Use the gapDistance to find final height
	{
		geometry.h = (text.first.h + texture.first.h) + gapDistance;
	}


	//Geometry when presset, for the sake of simplicity 
	pressedGeometry.w = int(geometry.w - (geometry.w * 0.05));
	pressedGeometry.h = int(geometry.h - (geometry.h * 0.05));
	pressedGeometry.x = geometry.x + ((geometry.w - pressedGeometry.w) / 2);
	pressedGeometry.y = geometry.y + ((geometry.h - pressedGeometry.h) / 2);


	//Query format for target texture and create
	Uint32 format;
	SDL_QueryTexture(texture.second, &format, NULL, NULL, NULL);
	this->texture = SDL_CreateTexture(renderer, format,
		SDL_TEXTUREACCESS_TARGET,
		geometry.w, geometry.h);

	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);

	SDL_Texture* target = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, this->texture);
	SDL_RenderCopy(renderer, texture.second, NULL, &texture.first);
	SDL_RenderCopy(renderer, text.second, NULL, &text.first);
	SDL_SetRenderTarget(renderer, target);

}

ButtonComponent::~ButtonComponent()
{
	destroy();
}

void ButtonComponent::render(SDL_Renderer* renderer, SDL_Texture* target)
{
	SDL_SetRenderTarget(renderer, target);
	if (pressed)
	{
		SDL_RenderCopy(renderer, texture, NULL, &pressedGeometry);
		return;
	}
	SDL_RenderCopy(renderer, texture, NULL, &geometry);
}

void ButtonComponent::handleEvent(SDL_Event* evt)
{
	if (is_inside(evt->motion.x, evt->motion.y))
	{
		switch (evt->type)
		{
			case SDL_MOUSEBUTTONUP:
			{
				pressed = false;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				pressed = true;
				owner->react_on_button(type);
				break;
			}
		default:
			break;
		}
	}
	else
	{
		pressed = false;
	}
	
}

SDL_Rect ButtonComponent::getGeometry() const
{
	return geometry;
}

void ButtonComponent::destroy()
{
	SDL_DestroyTexture(texture);
}


bool ButtonComponent::is_inside(int x, int y)
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
