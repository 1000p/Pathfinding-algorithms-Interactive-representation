#include "ResourceInitializer.h"

#include "RenderManager.h"
//#include "Node.h"

SDL_Texture* ResourceInitializer::openT = nullptr;
SDL_Texture* ResourceInitializer::closedT = nullptr;
SDL_Texture* ResourceInitializer::startT = nullptr;
SDL_Texture* ResourceInitializer::endT = nullptr;
SDL_Texture* ResourceInitializer::pathT = nullptr;
SDL_Texture* ResourceInitializer::obstacleT = nullptr;
SDL_Texture* ResourceInitializer::whiteT = nullptr;
SDL_Texture* ResourceInitializer::hoverT = nullptr;

TTF_Font* ResourceInitializer::font = nullptr;

void ResourceInitializer::init()
{
	initializeNodeTextures();
	initializeFont();
}

SDL_Texture* ResourceInitializer::getTexture(NodeState type) const
{
	switch (type)
	{
	case NodeState::OPEN:
	{
		return openT;

	}
	case NodeState::CLOSED:
	{
		return closedT;

	}
	case NodeState::START:
	{
		return startT;
	}
	case NodeState::END:
	{
		return endT;
	}
	case NodeState::PATH:
	{
		return pathT;
	}
	case NodeState::OBSTACLE:
	{
		return obstacleT;
	}
	case NodeState::WHITE:
	{
		return whiteT;
	}
	case NodeState::HOVER:
	{
		return hoverT;
	}
	default:
		return nullptr;
	}
}

TTF_Font* ResourceInitializer::getFont() const
{
	return font;
}

void ResourceInitializer::initializeNodeTextures()
{
	SDL_Renderer* renderer = RenderManager::getRenderer();

	//SDL_ShowWindow(RenderManager::getWindow());

	//Check if textures are initialized
	if (openT != nullptr || closedT != nullptr || startT != nullptr ||
		endT != nullptr || pathT != nullptr || obstacleT != nullptr ||
		whiteT != nullptr)
	{
		std::cout << "Textures already initialized!" << std::endl;
		return;
	}

	//Load surfaces from files
	SDL_Surface* open = IMG_Load("Tiles/opened.png");
	SDL_Surface* close = IMG_Load("Tiles/closed.png");
	SDL_Surface* start = IMG_Load("Tiles/start.png");
	SDL_Surface* end = IMG_Load("Tiles/end.png");
	SDL_Surface* path = IMG_Load("Tiles/path.png");
	SDL_Surface* obstacle = IMG_Load("Tiles/obstacle.png");
	SDL_Surface* white = IMG_Load("Tiles/white.png");
	SDL_Surface* hover = IMG_Load("Tiles/hover.png");

	//If any surface is not initialized exit
	if (open == nullptr || close == nullptr || start == nullptr ||
		end == nullptr || path == nullptr || obstacle == nullptr ||
		white == nullptr || hover == nullptr)
	{
		std::cout << "Could not load tile/s surfaces!" << std::endl;
		exit(-404);
	}

	//TEST
	SDL_RenderClear(renderer);

	//Create textures from surfaces and global renderer
	openT = SDL_CreateTextureFromSurface(renderer, open);
	closedT = SDL_CreateTextureFromSurface(renderer, close);
	startT = SDL_CreateTextureFromSurface(renderer, start);
	endT = SDL_CreateTextureFromSurface(renderer, end);
	pathT = SDL_CreateTextureFromSurface(renderer, path);
	obstacleT = SDL_CreateTextureFromSurface(renderer, obstacle);
	whiteT = SDL_CreateTextureFromSurface(renderer, white);
	hoverT = SDL_CreateTextureFromSurface(renderer, hover);

	/*SDL_ShowWindow(RenderManager::getWindow());
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, hoverT, NULL, NULL);
	SDL_RenderPresent(renderer);*/

	//If any texture is not initialized exit
	if (openT == nullptr || closedT == nullptr || startT == nullptr ||
		endT == nullptr || pathT == nullptr || obstacleT == nullptr ||
		whiteT == nullptr || hoverT == nullptr)
	{
		std::cout << "Could not load tile/s textures from surfaces!" << std::endl;
		exit(-404);
	}
	//Release resources
	SDL_FreeSurface(open);
	SDL_FreeSurface(close);
	SDL_FreeSurface(start);
	SDL_FreeSurface(end);
	SDL_FreeSurface(path);
	SDL_FreeSurface(obstacle);
	SDL_FreeSurface(white);
	SDL_FreeSurface(hover);
}

void ResourceInitializer::initializeFont()
{
	TTF_Init();
	font = TTF_OpenFont("Font.ttf", 24);
	if (!font)
	{
		std::cout << "Error loading font!" << std::endl;
		exit(-404);
	}
}
