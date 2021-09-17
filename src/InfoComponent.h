#pragma once
#include "Component.h"

#include "SDL_ttf.h"

#include <vector>

class MainWindow;

//Can be used as a sidebar or anything containing textures/information/buttons
class InfoComponent: public Component
{
public:

	InfoComponent(MainWindow* owner);

	virtual ~InfoComponent();

	SDL_Rect getGeometry() const;

	virtual void render(SDL_Renderer* renderer, SDL_Texture* target) override;

	SDL_Texture* getTexture();

	bool is_inside(int x, int y);

	// Inherited via Component
	virtual void handleEvent(SDL_Event* evt) override;

	virtual void destroy() override;

private:

	void init();

	std::vector<Component*> elements;
	MainWindow* owner;
	SDL_Texture* background;
	TTF_Font* font;
	SDL_Rect geometry;
	
};

