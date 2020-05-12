#pragma once

#include "NodesMap.h"

#include <iostream>
#include "SDL.h"

class RenderManager
{
public:
    RenderManager()
    {} 

    static void InitialMapRender(NodesMap* map) 
    {
        SDL_ShowWindow(window);
        //Declare padding and get map size
        int paddingTB, paddingLR; //TB = top/botton; LR = left right
        int mapW = map->_width;
        int mapH = map->_height;
        
        //Get size of a texture tile
        int textureSide;
        Uint32 format;
        SDL_QueryTexture(Node::whiteT, &format, NULL, &textureSide, NULL);

        //Get padding for bottom and top      
        int divident = (windowW < windowH) ? windowW : windowH ;       
        int tileScaledSize = (divident / mapH);

        //Catch the zero case
        tileScaledSize = tileScaledSize == 0 ? 1 : tileScaledSize;

        //Resize window so it fits the map only with no empty space,center the window
        windowW = mapW * tileScaledSize;
        windowH = mapH * tileScaledSize;
        SDL_SetWindowSize(window, windowW,windowH);
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

    static void renderMap(NodesMap* map)
    {
 
        int mapW = map->_width;
        int mapH = map->_height;
        int tileSize = map->tileSize;

        //Destination rect
        SDL_Rect dst{ map->x,map->y,tileSize,tileSize };

        //Destination texture
        SDL_Texture* outTex = SDL_CreateTexture(renderer, map->texturesFomat, SDL_TEXTUREACCESS_TARGET,
            windowW, windowH);

        //Set output texture as rendering target and clear the renderer
       // SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, outTex);
        

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
            dst.x = 0;
        }
       
        //Present rendering to texture
        SDL_RenderPresent(renderer);
        //Set rendering target to default, clear renderer, copy texture, present
        SDL_SetRenderTarget(renderer, NULL);
        //SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, outTex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    static SDL_Window* getWindow() 
    {
        return window;
    }

    static SDL_Renderer* getRenderer()
    {
        return renderer;
    }

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static int windowW;
    static int windowH;
    static void createRendererAndWindow(const int width,const int height);

    friend class InputManager;
};

