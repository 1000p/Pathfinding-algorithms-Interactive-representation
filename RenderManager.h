#pragma once

#include "NodesMap.h"

#include <iostream>
#include "SDL.h"

class RenderManager
{
public:
    RenderManager()
    {} 

    static void renderMap(const NodesMap* map) 
    {
        //Declare padding and get map size
        int paddingTB, paddingLR; //TB = top/botton; LR = left right
        int mapW = map->_width;
        int mapH = map->_height;
        
        //Get size of a texture tile
        int textureSide;
        Uint32 format;
        SDL_QueryTexture(Node::whiteT, &format, NULL, &textureSide, NULL);

        //Get padding for bottom and top      
        int divident = (windowW > windowH) ? windowW : windowH ;
        //int divident = (divisor == windowW) ? windowH : windowW;
        
        int tileScaledSize = (divident / mapH);
        paddingTB = (windowH % tileScaledSize != 0 ?
            (windowH % tileScaledSize) / 2 : 0);
        //Get padding for left and right
        paddingLR = (windowW % tileScaledSize != 0 ?
            (windowW % tileScaledSize) / 2 : 0);

        //Destination rect
        SDL_Rect dst{ paddingLR,paddingTB,tileScaledSize,tileScaledSize };

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
                //TEST!!!
                /*SDL_SetRenderTarget(renderer, NULL);
                SDL_RenderCopy(renderer, vecPtr[it]->texture, NULL,NULL);
                SDL_RenderPresent(renderer);*/
                //Render to texture and change the next destination accordingly
                SDL_RenderCopy(renderer, vecPtr[it]->texture, NULL, &dst);
                dst.x += tileScaledSize;
                ++it;
            }
            dst.y += tileScaledSize;
            dst.x = paddingLR;
        }
        
        //Present rendering to texture
        SDL_RenderPresent(renderer);
        //Set rendering target to default, clear renderer, copy texture, present
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderClear(renderer);
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

