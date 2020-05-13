#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

#include "Component.h"

class ButtonComponent: public Component
{
public:
	ButtonComponent() : Component(),texture(nullptr), text(nullptr) {}

private:
	SDL_Texture* texture;
	SDL_Texture* text;

	SDL_Rect geometry;

	// Inherited via Component
	virtual void handleEvent() override;

	static TTF_Font* font;
};

