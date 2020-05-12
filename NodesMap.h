#pragma once

#include "Node.h"


#include <vector>


class NodesMap
{
	
public:

	NodesMap(int width, int height): _width(width), _height(height), lastHovered(nullptr)
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

	void handleInput(SDL_Event* evt)
	{
		switch (evt->type)
		{
		case SDL_MOUSEMOTION:
		{
			int X = evt->motion.x;
			int Y = evt->motion.y;
			//SDL_GetMouseState(&X, &Y);
			bool isInside = false;

			if (X >= x && X <= widthInPixels)
			{
				if (Y >= y && Y <= heightInPixels)
				{
					isInside = true;
					int col = ((X / tileSize)+1 ) ;//(X / tileSize) + 1;
					int row = ((Y / tileSize) );//(Y / tileSize) + 1;
					int itx = (row * _width) + col-1;//((col * row)*row) - 1; //* row;
					Node* node = nodes[itx];
					if (node != lastHovered && lastHovered != nullptr)
					{
						lastHovered->changeState(NodeState::WHITE);
					}
						node->handleEvent(evt);

					
				}
			}
		}
		default:
			break;
		}
	}
	
	void setLastHovered(Node* last)
	{
		lastHovered = last;
	}

private:

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

	int x;
	int y;
	int tileSize;
	int _width;
	int _height;
	Node* lastHovered;

	Uint32 texturesFomat;

	int widthInPixels;
	int heightInPixels;
	std::vector<Node*> nodes;

	friend class RenderManager;
};

