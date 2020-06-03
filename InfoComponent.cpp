#include "InfoComponent.h"

#include "ButtonComponent.h"
#include "CheckBoxComponent.h"
#include "RenderManager.h"
#include "ResourceInitializer.h"
#include "MainWindow.h"

#include "SDL_image.h"

InfoComponent::InfoComponent(MainWindow* owner) : Component(), owner(owner)
{
	init();
}

InfoComponent::~InfoComponent()
{
	destroy();
}

SDL_Rect InfoComponent::getGeometry() const
{
	return geometry;
}

void InfoComponent::render(SDL_Renderer* renderer, SDL_Texture* target)
{
	SDL_SetRenderTarget(renderer, target);
	SDL_RenderCopy(renderer, background, NULL, &geometry);
	for (auto elem : elements)
	{
		elem->render(renderer, target);
		std::cout << SDL_GetError();
	}
}

SDL_Texture* InfoComponent::getTexture()
{
	return background;
}

bool InfoComponent::is_inside(int x, int y)
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

void InfoComponent::handleEvent(SDL_Event* evt)
{
	for (auto elem : elements)
	{
		elem->handleEvent(evt);
	}
}

void InfoComponent::destroy()
{
	elements.clear();
	SDL_DestroyTexture(background);
}

void InfoComponent::init()
{
	//Get resource init, the program window and renderer
	ResourceInitializer& resourceInit = ResourceInitializer::getInstance();
	SDL_Window* window = RenderManager::getWindow();
	SDL_Renderer* renderer = RenderManager::getRenderer();

	//Vector to store temporary texture data with its geometry
	std::vector<std::pair<SDL_Rect, SDL_Texture*>> textures;

	//Font in with which we will render text
	font = resourceInit.getFont();

	//Get window data
	int W, H;
	SDL_GetWindowSize(window, &W, &H);

	//Get tile data
	int tileSide;
	Uint32 format;
	SDL_Texture* tile = resourceInit.getTexture(NodeState::OBSTACLE);
	SDL_QueryTexture(tile, &format, NULL, &tileSide, NULL);

	//Destination rect for texture geometry
	SDL_Rect dst{ 0,0,W,55 };
	SDL_Rect textDst;

	//Final texture geometry
	geometry = dst;

	//Create texture to render to
	background = SDL_CreateTexture(renderer,
		format, SDL_TEXTUREACCESS_TARGET, W, 55);
	
	int textBoxWidth = 50;
	std::vector<SDL_Rect> tileDestinations;
	tileDestinations.reserve(6);

	//Add the first tile to the vector
	dst.x = 5; dst.y = 5; dst.w = tileSide; dst.h = tileSide;

	//Create text texture for the first tile and add to vector
	SDL_Color textColor{ 255,255,255 };
	SDL_Surface* text = TTF_RenderText_Blended(font, "Obstacle", textColor);
	SDL_Texture* textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);
	tileDestinations.push_back(dst);

	textDst.x = dst.x + tileSide + 5; textDst.y = dst.y;
	textDst.w = textBoxWidth; textDst.h = dst.h;

	elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::OBSTACLE, owner, renderer));
	SDL_DestroyTexture(textT);

	//Modifier to skip a tile
	int mod = tileSide + 5;

	//Do the same for the secound tile and text
	tile = resourceInit.getTexture(NodeState::OPEN);
	dst.x = tileDestinations[0].x; dst.y = tileDestinations[0].y + mod;
	dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "Opened", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + mod; textDst.y = dst.y;

	textures.push_back(std::make_pair(dst, tile));
	textures.push_back(std::make_pair(textDst, textT));

	//For the 3rd tile and text
	tile = resourceInit.getTexture(NodeState::START);
	dst.x = mod + textBoxWidth + 10; dst.y = 5; dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "START", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + mod; textDst.y = dst.y;

	elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::START, owner, renderer));
	SDL_DestroyTexture(textT);

	//For the 4th tile and text
	tile = resourceInit.getTexture(NodeState::CLOSED);
	dst.x = tileDestinations[2].x; dst.y = mod + 5; dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "Closed", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + mod; textDst.y = dst.y;

	textures.push_back(std::make_pair(dst, tile));
	textures.push_back(std::make_pair(textDst, textT));
		
	//For the 5th tile and text
	tile = resourceInit.getTexture(NodeState::END);
	dst.x = tileDestinations[2].x + textBoxWidth + mod + 5; dst.y = 5 ; dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "END", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + mod; textDst.y = dst.y;

	elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::END, owner, renderer));
	SDL_DestroyTexture(textT);
	
	//For the 6th tile and text
	tile = resourceInit.getTexture(NodeState::PATH);
	dst.x = tileDestinations[4].x; dst.y = mod+5; dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "PATH", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + tileSide + 5; textDst.y = dst.y;
	textures.push_back(std::make_pair(dst, tile));
	textures.push_back(std::make_pair(textDst, textT));

	//Create "choose algorithm" button
	textColor.b = textColor.g = textColor.r = 0;
	text = TTF_RenderText_Blended(font, "Choose Algoritm", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);
	textDst = elements[2]->getGeometry();
	textDst.x += textDst.w;
	textDst.h = 15; //Just so the text dont overlap with the button sidewalls

	//I use tile for the button texture here
	tile = IMG_LoadTexture(renderer, "Source/yellow_button.png");
	dst.x = textDst.x + 5; dst.w = 114; //95 and 30 is 1/2 of the button size scaled
	dst.y = textDst.y; dst.h =  25;
	textDst.w = 90; // Just so the text dont overlap with the button sidewalls
	//Center the text in the button
	textDst.x = dst.x + ((dst.w - textDst.w) / 2);
	textDst.y = dst.y + ((dst.h - textDst.h) / 2);

	elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::CHOOSE_ALGORITHM, owner,renderer));
	///##############################################################
	//Create the instant checkbox
	text = TTF_RenderText_Blended(font, "Instant ?", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);
	textDst = elements[3]->getGeometry();
	textDst.x += textDst.w;
	textDst.h = 20; //Text height in pixels

	//I use tile for the checkbox texture here
	tile = IMG_LoadTexture(renderer, "Source/checkbox.png");
	dst.x = textDst.x + 5; dst.w = 72; //72 = checkbox.png width in pixels
	dst.y = textDst.y; dst.h = 36;// 36 = checkbox.png height in pixels
	textDst.w = 60; // Text width in pixels
	elements.emplace_back(new CheckBoxComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::INSTANT_CHECKBOX, owner, renderer));
	
	SDL_Texture* target = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, background);
	SDL_SetRenderDrawColor(renderer, 135, 135, 135, 255);
	SDL_RenderClear(renderer);

	//Render static textures
	for (auto t : textures)
	{
		SDL_RenderCopy(renderer, t.second, NULL, &t.first);
	}

	//Render dynamic components
	SDL_SetRenderTarget(renderer, target);
	for (auto element : elements)
	{
		element->render(renderer, NULL);
	}
	
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
}
