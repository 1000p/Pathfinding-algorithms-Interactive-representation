#pragma once

#include "PhaseDefines.h"
#include "StateDefines.h"
#include "SDL.h"

#include <vector>
#include <list>

class Node;

class NodesMap
{
	
public:

	NodesMap(int width, int height);

	int getWidth() const;

	int getHeight() const;

	bool is_inside(int x, int y);

	void render(SDL_Renderer* renderer, SDL_Texture* target);

	void handleEvent(SDL_Event* evt);

	bool getEraser() const;

	void setEraser(bool value);

	NodeState getDrawTile() const;
	
	Node* getLastHovered() const;

	void setLastHovered(Node* last);

	Node* getStartNode() const;

	Node* getEndNode() const;

	void setStartNode(Node* node);

	void setEndNode(Node* node);

	void clearMap(Phase phase);
	
	void setPhase(Phase phase);

	Phase getPhase();

	std::vector<Node*> getNeighbours(Node* node);

private:

	Node* is_node(SDL_Event* evt);

	void drawCleanMap();

	bool eraser;
	int x;
	int y;
	int tileSize;
	int _width;
	int _height;
	Phase currentPhase;
	NodeState drawTile;
	Node* lastHovered;
	Node* startNode;
	Node* endNode;

	Uint32 texturesFomat;

	int xRight;
	int yBottom;

	int widthInPixels;
	int heightInPixels;
	std::vector<Node*> nodes;

	friend class RenderManager;

	friend class MainWindow;
};

