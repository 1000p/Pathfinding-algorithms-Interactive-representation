#include "CheckBoxComponent.h"

#include "MainWindow.h"

CheckBoxComponent::CheckBoxComponent(std::pair<SDL_Rect, SDL_Texture*> texture, std::pair<SDL_Rect, SDL_Texture*> text, ButtonType type, MainWindow* owner, SDL_Renderer* renderer)
	: Component(), type(type), togled(false), owner(owner)
{
	textureSprite = texture.second;
	geometryBox = texture.first;
	geometryText = text.first;
	textureText = text.second;
}

void CheckBoxComponent::handleEvent(SDL_Event* evt)
{
	if (is_inside(evt->motion.x, evt->motion.y))
	{
		switch (evt->type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			togled = togled != true ? true : false;
			owner->react_on_button(type);
			break;
		}
		default:
			break;
		}
	}
}

void CheckBoxComponent::render(SDL_Renderer* renderer, SDL_Texture* target)
{
	SDL_SetRenderTarget(renderer, target);
	SDL_Rect dst{ geometryBox.x,geometryBox.y,geometryBox.w / 2,geometryBox.h };
	if (togled)
	{
		SDL_Rect src
		{ geometryBox.w / 2,0,geometryBox.w / 2, geometryBox.h };

		SDL_RenderCopy(renderer, textureSprite,&src , &dst);
		
	}
	else
	{
		SDL_Rect src
		{ 0,0,geometryBox.w / 2, geometryBox.h };
		SDL_RenderCopy(renderer, textureSprite, &src, &dst);
	}
	dst.x += dst.w + 5; dst.w = geometryText.w;
	SDL_RenderCopy(renderer, textureText, NULL, &dst);

}

SDL_Rect CheckBoxComponent::getGeometry() const
{
    return geometryBox;
}

void CheckBoxComponent::destroy()
{
}

bool CheckBoxComponent::is_inside(int x, int y)
{
	if (x >= geometryBox.x && x <= geometryBox.x + (geometryBox.w/2))
	{
		if (y >= geometryBox.y && y <= geometryBox.y + geometryBox.h)
		{
			return true;
		}
	}
	return false;
}
