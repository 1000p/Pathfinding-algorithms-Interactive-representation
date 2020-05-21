#include "NodesMap.h"

int NodesMap::getWidth() const
{
	return _width;
}

int NodesMap::getHeight() const
{
	return _height;
}

bool NodesMap::is_inside(int x, int y)
{
	if (x >= this->x && x <= xRight)
	{
		if (y >= this->y && y <= yBottom)
		{
			return true;
		}
	}
	return false;
}

bool NodesMap::getEraser() const
{
	return eraser;
}

void NodesMap::setEraser(bool value)
{
	eraser = value;
}

Node* NodesMap::getLastHovered() const
{
	return lastHovered;
}

void NodesMap::setLastHovered(Node* last)
{
	lastHovered = last;
}

Node* NodesMap::getStartNode() const
{
	return startNode;
}

Node* NodesMap::getEndNode() const
{
	return endNode;
}

void NodesMap::setStartNode(Node* node)
{
	if (node == nullptr)
	{
		startNode = nullptr;
		return;
	}
	startNode = node;
}

Node* NodesMap::is_node(SDL_Event* evt)
{
	int X = evt->motion.x;
	int Y = evt->motion.y;

	if (X >= x && X <= xRight)
	{
		X = abs(X - x);
		if (Y >= y && Y <= yBottom)
		{
			Y = abs(Y - y);
			int col = ((X / tileSize)) == _width ? (X / tileSize) - 1 : (X / tileSize);
			int row = ((Y / tileSize));
			int index = ((row * _width) + col);
			Node* node = nodes[index];
			return node;
		}
	}
	return nullptr;
}
