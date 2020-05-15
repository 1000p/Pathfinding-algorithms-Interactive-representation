#pragma once

#include "Node.h"
#include "PhaseDefines.h"

#include <vector>


class NodesMap
{
	
public:

	NodesMap(int width, int height): _width(width), _height(height),eraser(false), lastHovered(nullptr),
		currentPhase(Phase::P_OBSTACLE)
	{
		nodes.reserve(width * height);
		drawCleanMap();
	}

	int getWidth() const
	{
		return _width;
	}

	int getHeight() const
	{
		return _height;
	}

	void handleEvent(SDL_Event* evt)
	{
		switch (evt->type)
		{
		case SDL_MOUSEMOTION:
		{
			Node* node = is_node(evt);
			if (node)
			{
				/*if (node != lastHovered && lastHovered != nullptr)
				{
					lastHovered->changeState(NodeState::WHITE);
				}*/
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

	bool getEraser() const
	{
		return eraser;
	}

	void setEraser(bool value)
	{
		eraser = value;
	}

	Phase getPhase() const
	{
		return currentPhase;
	}
	
	Node* getLastHovered() const
	{
		return lastHovered;
	}

	void setLastHovered(Node* last)
	{
		lastHovered = last;
	}

private:

	Node* is_node(SDL_Event* evt)
	{
		int X = evt->motion.x ;
		int Y = evt->motion.y;

		if (X >= x && X <= xRight)
		{
			X = abs(X - x);
			if (Y>=y && Y<=yBottom)
			{
				Y = abs(Y - y);
				int col = ((X / tileSize)) == _width ? (X / tileSize)-1: (X / tileSize);
				int row = ((Y / tileSize));
				int index = ((row * _width) + col);
				Node* node = nodes[index];
				return node;
			}
		}
		return nullptr;
	}

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
	Phase currentPhase;
	Node* lastHovered;
	

	Uint32 texturesFomat;

	int xRight;
	int yBottom;

	int widthInPixels;
	int heightInPixels;
	std::vector<Node*> nodes;

	friend class RenderManager;

	friend class MainWindow;
};

