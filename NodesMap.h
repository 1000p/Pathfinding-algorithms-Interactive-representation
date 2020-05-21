#pragma once

#include "Node.h"
#include "PhaseDefines.h"

#include <vector>


class NodesMap
{
	
public:

	NodesMap(int width, int height): _width(width), _height(height),eraser(false), lastHovered(nullptr),
		drawTile(NodeState::HOVER)
	{
		nodes.reserve(width * height);
		drawCleanMap();
	}

	int getWidth() const;

	int getHeight() const;

	bool is_inside(int x, int y);

	void handleEvent(SDL_Event* evt)
	{
		switch (evt->type)
		{
		case SDL_MOUSEMOTION:
		{
			Node* node = is_node(evt);
			if (node)
			{
				node->handleEvent(evt);
			}
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			Node* node = is_node(evt);
			if (node)
			{
				node->handleEvent(evt);
			}
			break;
		}
		default:
			break;
		}
	}

	bool getEraser() const;

	void setEraser(bool value);

	NodeState getDrawTile () const
	{
		return drawTile;
	}
	
	Node* getLastHovered() const;

	void setLastHovered(Node* last);

	Node* getStartNode() const;

	Node* getEndNode() const;

	void setStartNode(Node* node);

	void setEndNode(Node* node)
	{
		endNode = node;
	}

private:

	Node* is_node(SDL_Event* evt);

	void drawCleanMap()
	{
		for (int row = 0; row < _width; ++row)
		{
			for (int col = 0; col < _height; ++col)
			{
				nodes.push_back(new Node{ NodeState::WHITE, row, col,this });
			}
		}
	}

	bool eraser;
	int x;
	int y;
	int tileSize;
	int _width;
	int _height;
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

