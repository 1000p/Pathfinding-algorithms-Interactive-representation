#include "MainWindow.h"

#include "NodesMap.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceInitializer.h"
#include "AStarPathfinder.h"
#include "PopUpWindow.h"
#include "RecursiveDivision.h"


MainWindow::MainWindow() : map(nullptr), infoBar(nullptr),
pathFindingAlgorithm(nullptr),mazeGenAlgorithm(nullptr), instantAlgorithm(false)
{

    InputManager& inputManager = InputManager::getInstance();
    inputManager.init(&map, this);
    window = RenderManager::getWindow();
    renderer = RenderManager::getRenderer();
    init();
    SDL_ShowWindow(RenderManager::getWindow());

}

void MainWindow::handleEvent(SDL_Event* evt)
{
    //If the algorithm pop up window is active 
    //in order to prevent input to other components
    if (algorithmWindow)
    {
        algorithmWindow->handleEvent(evt);
        return;
    }

    int x = evt->motion.x;
    int y = evt->motion.y;

    //Gives event handling to the corresponding components
    if (map->is_inside(x, y))
    {
        map->handleEvent(evt);
    }
    else if (infoBar->is_inside(x, y))
    {
        infoBar->handleEvent(evt);
    }

}

NodesMap* MainWindow::getMap() const
{
    return map;
}

void MainWindow::render()
{
    //If we choose an algorithm we need to change the nodes map acordingly
    if (pathFindingAlgorithm)
    {
        if (map->currentPhase == Phase::CAN_CALCULATE_PATH ||
            map->currentPhase == Phase::DYNAMIC_RETRACE)
        {
            map->clearMap(Phase::CAN_CALCULATE_PATH);
            pathFindingAlgorithm->findPath(map->startNode, map->endNode,instantAlgorithm,
             renderer, NULL);
        }
        else if (map->currentPhase == Phase::NO_START_OR_END)
        {
            map->clearMap(Phase::NO_START_OR_END);
        }
    }
    //Render all components
    map->render(renderer, NULL);
    infoBar->render(renderer, NULL);
    
    if (algorithmWindow)
    {
        algorithmWindow->render();
    }

    //In case of an error
    std::cout << SDL_GetError();

    //Present 
    SDL_RenderPresent(renderer);

}

//Depending on the button type received we execute behaviour
void MainWindow::react_on_button(ButtonType type)
{
    switch (type)
    {
    case ButtonType::START:
    {
        map->drawTile = NodeState::START;
        break;
    }
    case ButtonType::END:
    {
        map->drawTile = NodeState::END;
        break;
    }
    case ButtonType::OBSTACLE:
    {
        map->drawTile = NodeState::OBSTACLE;
        break;
    }
    case ButtonType::CHOOSE_ALGORITHM:
    {
        if (algorithmWindow)
        {
            algorithmWindow->close();
            algorithmWindow = nullptr;
        }
        else
        {
            algorithmWindow = new PopUpWindow(this, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS |
                SDL_WINDOW_SKIP_TASKBAR | SDL_WINDOW_INPUT_GRABBED |
                SDL_WINDOW_ALWAYS_ON_TOP, WindowType::PathAlgorithmPopUpWindow);
        }
        break;
    }
    case ButtonType::CHOOSE_MAZE:
    {
        if (algorithmWindow)
        {
            algorithmWindow->close();
            algorithmWindow = nullptr;
        }
        else
        {
            algorithmWindow = new PopUpWindow(this, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS |
                SDL_WINDOW_SKIP_TASKBAR | SDL_WINDOW_INPUT_GRABBED |
                SDL_WINDOW_ALWAYS_ON_TOP, WindowType::MazeAlgorithmPopUpWindow);
        }
        break;
    }
    case ButtonType::INSTANT_CHECKBOX:
    {
        if (instantAlgorithm == false)
        {
            instantAlgorithm = true;
        }
        else
        {
            instantAlgorithm = false;
        }
       
        break;
    }
    case ButtonType::A_STAR_ALGORITHM:
    {
        if (algorithmWindow)
        {
            algorithmWindow->close();
            algorithmWindow = nullptr;
        }

        if (pathFindingAlgorithm)
        {
            delete pathFindingAlgorithm;
            pathFindingAlgorithm = nullptr;
        }
        pathFindingAlgorithm = new AStarPathfinder();
        break;
    }
    case ButtonType::RECURSIVE_DIVISION:
    {
        if (algorithmWindow)
        {
            algorithmWindow->close();
            algorithmWindow = nullptr;
        }

        if (mazeGenAlgorithm)
        {
            delete mazeGenAlgorithm;
            mazeGenAlgorithm = nullptr;
        }
        mazeGenAlgorithm = new RecursiveDivision(2);
        mazeGenAlgorithm->generateMaze(map,renderer);
        break;
    }
    default:
        break;
    }
}

void MainWindow::init()
{
    SDL_ShowWindow(window);

    //Declare padding and get map size
    int paddingLR; 
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

    _height -= 55; // infobar height

    //Get padding for bottom and top      
    int divident = (_width < _height) ? _width : _height;
    int divisor = (mapW < mapH) ? mapH : mapW;
    int tileScaledSize = (divident / divisor);

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
