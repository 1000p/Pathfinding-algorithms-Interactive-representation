#pragma once
#include "InputManager.h"
#include "NodesMap.h"
#include "InfoComponent.h"
#include "ResourceInitializer.h"

class MainWindow
{
public:

	MainWindow(): map(nullptr),infoBar(nullptr)
	{

		InputManager& inputManager = InputManager::getInstance();
		inputManager.init(&map);
        window = RenderManager::getWindow();
        renderer = RenderManager::getRenderer();
        init();
		SDL_ShowWindow(RenderManager::getWindow());
	}

	NodesMap* getMap() const
	{
		return map;
	}

    void render()
    {
        int mapW = map->_width;
        int mapH = map->_height;
        int tileSize = map->tileSize;

        //Destination rect
        SDL_Rect dst{ map->x,map->y,tileSize,tileSize };

        //Destination texture
        SDL_Texture* outTex = SDL_CreateTexture(renderer, map->texturesFomat, SDL_TEXTUREACCESS_TARGET,
            _width, _height);

        //Set output texture as rendering target and clear the renderer
       // SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, outTex);

        //SDL_RenderClear(renderer);

        //Iterate over the map
        int it = 0;
        const std::vector<Node*>& vecPtr = map->nodes;
        for (int row = 0; row < mapH; ++row)
        {
            for (int col = 0; col < mapW; ++col)
            {
                //Render to texture and change the next destination accordingly
                SDL_RenderCopy(renderer, vecPtr[it]->texture, NULL, &dst);

                dst.x += tileSize;
                ++it;
            }
            dst.y += tileSize;
            dst.x = map->x;
        }
        infoBar->render(renderer, outTex);
       
        std::cout << SDL_GetError();


        //Present rendering to texture
        SDL_RenderPresent(renderer);
        //Set rendering target to default, clear renderer,
        //copy texture, present
        SDL_SetRenderTarget(renderer, NULL);
        //SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, outTex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

private:

	void init()
	{
        SDL_ShowWindow(window);

         //Declare padding and get map size
        int paddingTB, paddingLR; //TB = top/botton; LR = left right
        int mapW = map->_width;
        int mapH = map->_height;

        //Get window width/height     
        SDL_GetWindowSize(window, &_width, &_height);

        //Get size of a texture tile
        int textureSide;
        Uint32 format;
        SDL_QueryTexture(ResourceInitializer::getInstance().ResourceInitializer::getTexture(NodeState::WHITE),
            &format, NULL, &textureSide, NULL);

        //###########INFOBAR CREATING WAS HERE !!!!!!!!!!!
        _height -= 55;

        //Get padding for bottom and top      
        int divident = (_width < _height) ? _width : _height;
        int tileScaledSize = (divident / mapH);

        //Catch the zero case
        tileScaledSize = tileScaledSize == 0 ? 1 : tileScaledSize;

        //Resize window so it fits the map only with no empty space,center the window
        _width = mapW * tileScaledSize;
        _height = mapH * tileScaledSize;
        _width = _width >= 500 ? _width : 500;
        _height += 55; // RELATES ON INFOBAR HEIGHT !!!!!#######

        SDL_SetWindowSize(window, _width, _height);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        //Inform user about resizing
        std::cout << "\nThe program window was resized so wraps the tile map!\n" <<
            "New size: " << _width << " x " << _height << std::endl;

        //Initialize the status bar
        infoBar = new InfoComponent();
        SDL_Rect geometry = infoBar->getGeometry();

        //TODO: use the padding vars when intruducing action bar
        /*
        paddingTB = (windowH % tileScaledSize != 0 ?
        (windowH % tileScaledSize) / 2 : 0);
        */
        //Get padding for left and right
        paddingLR = (_width - (tileScaledSize * mapW) != 0 ?
        (_width - (tileScaledSize * mapW)) / 2 : 0);
        

        //Destination rect
        SDL_Rect dst{ paddingLR,geometry.y+geometry.h,tileScaledSize,tileScaledSize };

        //Sets node map coordinates, node size, textures format and dimensions in pixels
        map->x = dst.x;
        map->y = dst.y;
        map->tileSize = tileScaledSize;
        map->widthInPixels = tileScaledSize * mapW;
        map->heightInPixels = tileScaledSize * mapH;
        map->xRight = dst.x + map->widthInPixels;
        map->yBottom = dst.y + map->heightInPixels;
        map->texturesFomat = format;

        //Destination texture
        SDL_Texture* outTex = SDL_CreateTexture(renderer, format,
            SDL_TEXTUREACCESS_TARGET,
            _width, _height);


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
                //Render to texture and change the next destination accordingly
                SDL_RenderCopy(renderer, vecPtr[it]->texture, NULL, &dst);
                dst.x += tileScaledSize;
                ++it;
            }
            dst.y += tileScaledSize;
            dst.x = paddingLR;
        }
        SDL_RenderCopy(renderer, infoBar->getTexture(), NULL, &geometry);

        //Set rendering target to default, clear renderer, 
        //copy texture, present
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, outTex, NULL, NULL);
        SDL_RenderPresent(renderer);
	}

    SDL_Window* window;
    SDL_Renderer* renderer;
	NodesMap* map;
	InfoComponent* infoBar;

    int _width;
    int _height;
};

