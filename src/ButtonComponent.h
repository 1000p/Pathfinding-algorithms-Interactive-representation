#pragma once

#include "Component.h"
#include "ButtonDefines.h"

#include <utility>


class MainWindow;

class ButtonComponent: public Component
{
public:
	ButtonComponent(std::pair <SDL_Rect, SDL_Texture*> texture,
		std::pair <SDL_Rect, SDL_Texture*> text, ButtonType type,MainWindow* owner,
		SDL_Renderer* renderer);

	virtual ~ButtonComponent() override;

	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) override;

	// Inherited via Component
	virtual void handleEvent(SDL_Event* evt) override;

	virtual SDL_Rect getGeometry() const override;

	virtual void destroy() override;

private:

	bool is_inside(int x, int y);

	bool pressed;
	MainWindow* owner;
	SDL_Texture* texture;
	ButtonType type;
	SDL_Rect geometry;
	SDL_Rect pressedGeometry;
};

