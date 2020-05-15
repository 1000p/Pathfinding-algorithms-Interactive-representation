#pragma once

#include "NodesMap.h"

#include <iostream>
#include "SDL.h"

class RenderManager
{
public:
    RenderManager()
    {} 

    //static void InitialMapRender(NodesMap* map);

    /*
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
    }*/

  
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

