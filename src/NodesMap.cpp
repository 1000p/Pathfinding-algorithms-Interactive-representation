#include "NodesMap.h"

#include "Node.h"
#include "StateDefines.h"

NodesMap::NodesMap(int width, int height) : _width(width), _height(height), eraser(false), lastHovered(nullptr),
drawTile(NodeState::HOVER), currentPhase(Phase::DEFAULT)
{
	nodes.reserve(width * height);
	drawCleanMap();
}

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

void NodesMap::render(SDL_Renderer* renderer, SDL_Texture* target)
{
	SDL_Texture* lastTarget = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, target);

	//Destination rect
	SDL_Rect dst{ this->x,this->y,tileSize,tileSize };
	
	SDL_RenderClear(renderer);

	//Iterate over the map
	int it = 0;
	for (int row = 0; row < _height; ++row)
	{
		for (int col = 0; col < _width; ++col)
		{
			//Render to texture and change the next destination accordingly
			SDL_RenderCopy(renderer, nodes[it]->texture, NULL, &dst);

			dst.x += tileSize;
			++it;
		}
		dst.y += tileSize;
		dst.x = this->x;
	}

	SDL_SetRenderTarget(renderer, lastTarget);
}

void NodesMap::handleEvent(SDL_Event* evt)
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
		break;
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

bool NodesMap::getEraser() const
{
	return eraser;
}

void NodesMap::setEraser(bool value)
{
	eraser = value;
}

Node* NodesMap::getNode(int x, int y)
{
	int index = y * _width + x;//((row * _width) + col);

	if (index < nodes.size())
	{
		Node* node = nodes[index];
		if (node->getX() == x && node->getY() == y)
		{
			return node;
		}
	}

	return nullptr;
}

NodeState NodesMap::getDrawTile() const
{
	return drawTile;
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

void NodesMap::setEndNode(Node* node)
{
	endNode = node;
}

void NodesMap::clearMap(Phase phase)
{
	switch (phase)
	{
	case Phase::PATH_FOUND:
		break;
	case Phase::NO_START_OR_END:
	{	for (auto node : nodes)
	{
		if (node->state != NodeState::OBSTACLE && node->state != NodeState::WHITE)
		{
			node->memoryState = node->permanentState = NodeState::WHITE;
			node->changeState(NodeState::WHITE);
		}
	}
	if (startNode)
	{
		startNode->changeState(NodeState::START);
		startNode->memoryState = NodeState::WHITE;
		startNode->permanentState = startNode->state;
	}
	if (endNode)
	{
		endNode->changeState(NodeState::END);
		endNode->memoryState = NodeState::WHITE;
		endNode->permanentState = endNode->state;
	}
	currentPhase = Phase::DEFAULT;
	break;
	}
	case Phase::CAN_CALCULATE_PATH:
	{
		for (auto node : nodes)
		{
			if (node->state != NodeState::OBSTACLE && node->state != NodeState::WHITE)
			{
				node->memoryState = node->permanentState = NodeState::WHITE;
				node->changeState(NodeState::WHITE);
			}
		}
		if (startNode)
		{
			startNode->changeState(NodeState::START);
			startNode->memoryState = NodeState::WHITE;
			startNode->permanentState = startNode->state;
		}
		if (endNode)
		{
			endNode->changeState(NodeState::END);
			endNode->memoryState = NodeState::WHITE;
			endNode->permanentState = endNode->state;
		}
		currentPhase = Phase::DEFAULT;
		break;
	}
	case Phase::DYNAMIC_RETRACE:
		for (auto node : nodes)
		{
			if (node->state != NodeState::OBSTACLE && node->state != NodeState::WHITE)
			{
				node->memoryState = node->permanentState = NodeState::WHITE;
				node->changeState(NodeState::WHITE);
			}
		}
		break;
	case Phase::DEFAULT:
		break;
	default:
		break;
	}
}

void NodesMap::setPhase(Phase phase)
{
	currentPhase = phase;
}

Phase NodesMap::getPhase()
{
	return currentPhase;
}

std::vector<Node*> NodesMap::getNeighbours(Node* node)
{
	std::vector<Node*> neighbours(4, nullptr);
	neighbours.reserve(8);
	int nodeX = node->x;
	int nodeY = node->y;

	//above
	neighbours[0] = nodeY > 0 ? nodes[(_width * (nodeY - 1)) + nodeX] : nullptr;
	//below
	neighbours[1] = nodeY < _height - 1 ? nodes[(_width * (nodeY + 1)) + nodeX] : nullptr;
	//left
	neighbours[2] = nodeX > 0 ? nodes[(_width * nodeY) + (nodeX - 1)] : nullptr;
	//right
	neighbours[3] = nodeX < _width - 1 ? nodes[(_width * nodeY) + (nodeX + 1)] : nullptr;

	NodeState obstuction = NodeState::OBSTACLE;


	if ((neighbours[0] && neighbours[2]))
	{
		if (neighbours[0]->state != obstuction || neighbours[2]->state != obstuction)
		{
			//top-left
			neighbours.push_back(nodes[(_width * (nodeY - 1)) + (nodeX - 1)]);
		}
	}



	if ((neighbours[0] && neighbours[3]))
	{
		if (neighbours[0]->state != obstuction || neighbours[3]->state != obstuction)
		{
			//top-right
			neighbours.push_back(nodes[(_width * (nodeY - 1)) + (nodeX + 1)]);
		}
	}



	if ((neighbours[1] && neighbours[2]))
	{
		if (neighbours[1]->state != obstuction || neighbours[2]->state != obstuction)
		{
			//bottom-left
			neighbours.push_back(nodes[(_width * (nodeY + 1)) + (nodeX - 1)]);
		}
	}



	if ((neighbours[1] && neighbours[3]))
	{
		if (neighbours[1]->state != obstuction || neighbours[3]->state != obstuction)
		{
			//bottom-right
			neighbours.push_back(nodes[(_width * (nodeY + 1)) + (nodeX + 1)]);
		}
	}


	return neighbours;
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
			return nodes[index];
		}
	}
	return nullptr;
}

void NodesMap::drawCleanMap()
{
	for (int row = 0; row < _height; ++row)
	{
		for (int col = 0; col < _width; ++col)
		{
			nodes.push_back(new Node{ NodeState::WHITE, row, col,this });
		}
	}
}


