#include "InfoComponent.h"
#include "ResourceInitializer.h"

void InfoComponent::handleEvent()
{
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

	//Final texture geometry
	geometry = dst;

	//Create texture to render to
	/*SDL_Texture**/ background = SDL_CreateTexture(renderer,
		format, SDL_TEXTUREACCESS_TARGET, W, 55);
	
	//Add the first tile to the vector
	dst.x = 5; dst.y = 5; dst.w = tileSide; dst.h = tileSide;
	textures.push_back({ dst, tile });

	//Create text texture for the first tile and add to vector
	SDL_Color textColor{ 255,255,255 };
	SDL_Surface* text = TTF_RenderText_Blended(font, "Obstacle", textColor);
	SDL_Texture* textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	dst.x += tileSide + 5; dst.w = 50; 
	textures.push_back({ dst,textT });

	//Modifier to skip a tile
	int mod = tileSide + 5;

	//Do the same for the secound tile and text
	tile = resourceInit.getTexture(NodeState::OPEN);
	dst.x = textures[0].first.x; dst.y = textures[0].first.y + mod;
	dst.w = tileSide;
	textures.push_back({ dst, tile });

	text = TTF_RenderText_Blended(font, "Opened", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	dst.x += mod; dst.w = 50;
	textures.push_back({ dst,textT });

	//For the 3rd tile and text
	tile = resourceInit.getTexture(NodeState::START);
	dst.x = mod + 50 + 10; dst.y = 5; dst.w = tileSide;
	textures.push_back({ dst, tile });

	text = TTF_RenderText_Blended(font, "START", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	dst.x += mod; dst.w = 50;
	textures.push_back({ dst,textT });

	//For the 4th tile and text
	tile = resourceInit.getTexture(NodeState::CLOSED);
	dst.x = textures[4].first.x; dst.y = mod + 5; dst.w = tileSide;
	textures.push_back({ dst, tile });

	text = TTF_RenderText_Blended(font, "Closed", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	dst.x += mod; dst.w = 50;
	textures.push_back({ dst,textT });
	
	//For the 5th tile and text
	tile = resourceInit.getTexture(NodeState::END);
	dst.x = textures[5].first.x + 50 + 5; dst.y = 5 ; dst.w = tileSide;
	textures.push_back({ dst, tile });

	text = TTF_RenderText_Blended(font, "END", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	dst.x += mod; dst.w = 50;
	textures.push_back({ dst,textT });
	
	//For the 6th tile and text
	tile = resourceInit.getTexture(NodeState::PATH);
	dst.x = textures[8].first.x; dst.y = mod+5; dst.w = tileSide;
	textures.push_back({ dst, tile });

	text = TTF_RenderText_Blended(font, "PATH", textColor);
	textT = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);

	dst.x += tileSide + 5; dst.w = 50;
	textures.push_back({ dst,textT });
	
	//Render all element from the vector to the background
	SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, background);
	SDL_SetRenderDrawColor(renderer, 135, 135, 135,255);
	SDL_RenderClear(renderer);

	for (auto p : textures)
	{
		SDL_RenderCopy(renderer, p.second, NULL, &p.first);
	}
	
	//Set target to old target & clear the rederer
	SDL_SetRenderTarget(renderer, oldTarget);
	SDL_RenderClear(renderer);

	
}
