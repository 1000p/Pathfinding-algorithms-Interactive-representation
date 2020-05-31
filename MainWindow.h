#pragma once
#include "InputManager.h"
#include "NodesMap.h"
#include "InfoComponent.h"
#include "ResourceInitializer.h"
#include "ButtonDefines.h"



#include "AStarPathfinder.h"

class MainWindow
{
public:

	MainWindow(): map(nullptr),infoBar(nullptr)
	{

		InputManager& inputManager = InputManager::getInstance();
		inputManager.init(&map, this);
        window = RenderManager::getWindow();
        renderer = RenderManager::getRenderer();
        init();
		SDL_ShowWindow(RenderManager::getWindow());
	}

    void handleEvent(SDL_Event* evt)
    {
        int x = evt->motion.x;
        int y = evt->motion.y;

        if (map->is_inside(x, y))
        {
            map->handleEvent(evt);         
        }
        else if (infoBar->is_inside(x, y))
        {
            infoBar->handleEvent(evt);
        }

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

        //TEST LINE REMOVE AFTER 
        static bool rendered = false;
        if (map->currentPhase == Phase::CAN_CALCULATE_PATH ||
            map->currentPhase == Phase::DYNAMIC_RETRACE)
        {         
            rendered = true;
            AStarPathfinder aStar;
            map->clearMap(Phase::CAN_CALCULATE_PATH);
            aStar.findPath(map->startNode, map->endNode);
        }
        else if (map->currentPhase == Phase::NO_START_OR_END)
        {
            map->clearMap(Phase::NO_START_OR_END);
        }

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

                dst.x += tileSize;
                ++it;
            }
            dst.y += tileSize;
            dst.x = map->x;
        }
        infoBar->render(renderer, NULL);
       
        std::cout << SDL_GetError();

        //Present 
        SDL_RenderPresent(renderer);

    }

    void react_on_button(ButtonType type)
    {
        switch (type)
        {
        case ButtonType::START:
            map->drawTile = NodeState::START;
            break;
        case ButtonType::END:
            map->drawTile = NodeState::END;
            break;
        case ButtonType::OBSTACLE:
            map->drawTile = NodeState::OBSTACLE;
            break;
        default:
            break;
        }
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
        SDL_QueryTexture(ResourceInitializer::getInstance()
            .ResourceInitializer::getTexture(NodeState::WHITE),
            &format, NULL, &textureSide, NULL);

        //###########INFOBAR CREATING WAS HERE !
        _height -= 55; // infobar height

        //Get padding for bottom and top      
        int divident = (_width < _height) ? _width : _height;
        int tileScaledSize = (divident / mapH);

        //Catch the zero case
        tileScaledSize = tileScaledSize == 0 ? 1 : tileScaledSize;

        //Resize window so it fits the map only with no empty space,center the window
        _width = mapW * tileScaledSize;
        _height = mapH * tileScaledSize;
        _width = _width >= 500 ? _width : 500;
        _height += 55; // RELATES ON INFOBAR HEIGHT !

        SDL_SetWindowSize(window, _width, _height);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        //Inform user about resizing
        std::cout << "\nThe program window was resized so wraps the tile map!\n" <<
            "New size: " << _width << " x " << _height << std::endl;

        //Initialize the status bar
        infoBar = new InfoComponent(this);
        SDL_Rect geometry = infoBar->getGeometry();

        //TODO: use the padding vars when intruducing action bar
        /*
        paddingTB = (windowH % tileScaledSize != 0 ?
        (windowH % tileScaledSize) / 2 : 0);
        */

        //Get padding for left and right
        paddingLR = (_width - (tileScaledSize * mapW) != 0 ?
        (_width - (tileScaledSize * mapW)) / 2 : 0);

        //Sets node map coordinates, node size, textures format and dimensions in pixels
        map->x = paddingLR;
        map->y = geometry.y + geometry.h;
        map->tileSize = tileScaledSize;
        map->widthInPixels = tileScaledSize * mapW;
        map->heightInPixels = tileScaledSize * mapH;
        map->xRight = paddingLR + map->widthInPixels;
        map->yBottom = geometry.y + geometry.h + map->heightInPixels;
        map->texturesFomat = format;

        render();
	}

    SDL_Window* window;
    SDL_Renderer* renderer;
	NodesMap* map;
	InfoComponent* infoBar;


    int _width;
    int _height;
};

