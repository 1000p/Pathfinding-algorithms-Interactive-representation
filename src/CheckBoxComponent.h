#pragma once
#include "Component.h"
#include "ButtonDefines.h"

#include <utility>

class MainWindow;

class CheckBoxComponent: public Component
{
public:
	CheckBoxComponent(std::pair <SDL_Rect, SDL_Texture*> texture,
		std::pair <SDL_Rect, SDL_Texture*> text, ButtonType type, MainWindow* owner,
		SDL_Renderer* renderer);

	// Inherited via Component
	virtual void handleEvent(SDL_Event* evt) override;
	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) override;
	virtual SDL_Rect getGeometry() const override;
	virtual void destroy() override;

private:

	bool is_inside(int x, int y);

	SDL_Texture* textureSprite;
	SDL_Texture* textureText;
	MainWindow* owner;
	SDL_Rect geometryBox;
	SDL_Rect geometryText;
	ButtonType type;
	bool togled;
};

