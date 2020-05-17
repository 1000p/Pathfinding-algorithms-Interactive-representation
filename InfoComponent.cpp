#include "InfoComponent.h"
#include "ResourceInitializer.h"
#include "ButtonComponent.h"

void InfoComponent::handleEvent(SDL_Event* evt)
{
	for (auto elem : elements)
	{
		elem->handleEvent(evt);
	}
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
		ButtonType::OBSTACLE, owner));


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

	//elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT)));

	//For the 3rd tile and text
	tile = resourceInit.getTexture(NodeState::START);
	dst.x = mod + textBoxWidth + 10; dst.y = 5; dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "START", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + mod; textDst.y = dst.y;


	elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::START, owner));

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
	//elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT)));
	
	//For the 5th tile and text
	tile = resourceInit.getTexture(NodeState::END);
	dst.x = tileDestinations[2].x + textBoxWidth + mod + 5; dst.y = 5 ; dst.w = tileSide;
	tileDestinations.push_back(dst);

	text = TTF_RenderText_Blended(font, "END", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	textDst.x = dst.x + mod; textDst.y = dst.y;


	elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT),
		ButtonType::END, owner));
	
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
	//elements.emplace_back(new ButtonComponent(std::make_pair(dst, tile), std::make_pair(textDst, textT)));

	SDL_Texture* target = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, background);
	SDL_SetRenderDrawColor(renderer,135, 135, 135, 255);
	SDL_RenderClear(renderer);

	for (auto t : textures)
	{
		SDL_RenderCopy(renderer, t.second, NULL, &t.first);
	}

	SDL_SetRenderTarget(renderer, target);
	for (auto element : elements)
	{
		element->render(renderer, NULL);
	}
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
}
