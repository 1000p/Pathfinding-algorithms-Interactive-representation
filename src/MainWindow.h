#pragma once

#include "PathAlgorithm.h"
#include "InfoComponent.h"
#include "ButtonDefines.h"

class PopUpWindow;
class NodesMap;
class MazeAlgorithm;

class MainWindow
{
public:

    MainWindow();

    void handleEvent(SDL_Event* evt);

    NodesMap* getMap() const;

    void render();

    void react_on_button(ButtonType type);

private:

    void init();

    SDL_Window* window;
    SDL_Renderer* renderer;
	NodesMap* map;
	InfoComponent* infoBar;
    PopUpWindow* algorithmWindow;
    PathAlgorithm* pathFindingAlgorithm;
    MazeAlgorithm* mazeGenAlgorithm;

    int _width;
    int _height;
    bool instantAlgorithm;
};

