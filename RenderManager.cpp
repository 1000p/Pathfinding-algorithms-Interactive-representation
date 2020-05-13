#include "RenderManager.h"
#include "ResourceInitializer.h"

SDL_Renderer* RenderManager::renderer = nullptr;
SDL_Window* RenderManager::window = nullptr;
int RenderManager::windowW = 0;
int RenderManager::windowH = 0;

void RenderManager::InitialMapRender(NodesMap* map)
{
    SDL_ShowWindow(window);
    //Declare padding and get map size
    int paddingTB, paddingLR; //TB = top/botton; LR = left right
    int mapW = map->_width;
    int mapH = map->_height;

    //Get size of a texture tile
    int textureSide;
    Uint32 format;
    SDL_QueryTexture(ResourceInitializer::getInstance().ResourceInitializer::getTexture(NodeState::WHITE),
        &format, NULL, &textureSide, NULL);

    //Get padding for bottom and top      
    int divident = (windowW < windowH) ? windowW : windowH;
    int tileScaledSize = (divident / mapH);

    //Catch the zero case
    tileScaledSize = tileScaledSize == 0 ? 1 : tileScaledSize;

    //Resize window so it fits the map only with no empty space,center the window
    windowW = mapW * tileScaledSize;
    windowH = mapH * tileScaledSize;
    SDL_SetWindowSize(window, windowW, windowH);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    //Inform user about resizing
    std::cout << "\nThe program window was resized so wraps the tile map!\n" <<
        "New size: " << windowW << " x " << windowH << std::endl;

    //TODO: use the padding vars when intruducing action bar
    /*
    paddingTB = (windowH % tileScaledSize != 0 ?
    (windowH % tileScaledSize) / 2 : 0);
    //Get padding for left and right
    paddingLR = (windowW % tileScaledSize != 0 ?
    (windowW % tileScaledSize) / 2 : 0);
    */

    //Destination rect
    SDL_Rect dst{ 0,0,tileScaledSize,tileScaledSize };

    //Sets node map coordinates, node size, textures format and dimensions in pixels
    map->x = dst.x;
    map->y = dst.y;
    map->tileSize = tileScaledSize;
    map->widthInPixels = tileScaledSize * mapW;
    map->heightInPixels = tileScaledSize * mapH;
    map->texturesFomat = format;

    //Destination texture
    SDL_Texture* outTex = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET,
        windowW, windowH);

    //Set output texture as rendering target and clear the renderer
    SDL_SetRenderTarget(renderer, outTex);
    SDL_RenderClear(renderer);

    //Iterate over the map
    int it = 0;
    const std::vector<Node*>& vecPtr = map->nodes;
    for (int row = 0; row < mapH; ++row)
    {
        for (int col = 0; col < mapW; ++col)
        {
            //SDL_SetRenderTarget(renderer, outTex);
            //TEST!!!
            /*SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, vecPtr[it]->texture, NULL,NULL);
            SDL_RenderPresent(renderer);*/
            //Render to texture and change the next destination accordingly
            SDL_RenderCopy(renderer, vecPtr[it]->texture, NULL, &dst);
            //SDL_SetRenderTarget(renderer, NULL);
            //SDL_RenderCopy(renderer, outTex, NULL, NULL);
            // SDL_RenderPresent(renderer);
            dst.x += tileScaledSize;
            ++it;
        }
        dst.y += tileScaledSize;
        dst.x = 0;
    }
    /*
    //test
    int y = 474;
    int x = 1;

    int row = 474/tileScaledSize +1;
    int itx = ((((x / tileScaledSize) + 1) * row) - 1) * row;
    */

    //Present rendering to texture
    SDL_RenderPresent(renderer);
    //Set rendering target to default, clear renderer, copy texture, present
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, outTex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void RenderManager::createRendererAndWindow(const int width,const int height)
{
	//Create window
	window = SDL_CreateWindow("Visualizer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 
	 SDL_WINDOW_HIDDEN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED 
			| SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(renderer);
		}
	}

	windowW = width;
	windowH = height;
}
