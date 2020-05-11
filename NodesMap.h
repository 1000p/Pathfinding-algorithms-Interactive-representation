#pragma once

#include "Node.h"


#include <vector>


class NodesMap
{
	
public:

	NodesMap(int width, int height): _width(width), _height(height)
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

private:

	void drawCleanMap()
	{
		for (int row = 0; row < _width; ++row)
		{
			for (int col = 0; col < _height; ++col)
			{
				nodes.push_back(new Node{ NodeState::WHITE, row, col });
			}
		}
	}

	int _width;
	int _height;
	std::vector<Node*> nodes;

	friend class RenderManager;
};

