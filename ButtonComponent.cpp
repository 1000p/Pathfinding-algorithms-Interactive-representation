#include "ButtonComponent.h"

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
