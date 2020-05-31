#pragma once

#include "Node.h"
#include "PhaseDefines.h"

#include <vector>
#include <list>


class NodesMap
{
	
public:

	NodesMap(int width, int height): _width(width), _height(height),eraser(false), lastHovered(nullptr),
		drawTile(NodeState::HOVER), currentPhase(Phase::DEFAULT)
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

	void clearMap(Phase phase)
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
	
	void setPhase(Phase phase)
	{
		currentPhase = phase;
	}

	Phase getPhase()
	{
		return currentPhase;
	}

	std::vector<Node*> getNeighbours(Node* node)
	{
		std::vector<Node*> neighbours(4,nullptr);
		neighbours.reserve(8);
		int nodeX = node->x;
		int nodeY = node->y;

		//above
		neighbours[0] = nodeY > 0 ? nodes[(_width * (nodeY - 1)) + nodeX ] : nullptr;
		//below
		neighbours[1] = nodeY < _height-1 ? nodes[(_width * (nodeY + 1)) + nodeX] : nullptr;
		//left
		neighbours[2] = nodeX > 0 ? nodes[(_width * nodeY) + (nodeX - 1)] : nullptr;
		//right
		neighbours[3] = nodeX < _width-1 ? nodes[(_width * nodeY) + (nodeX + 1)] : nullptr;

		NodeState obstuction = NodeState::OBSTACLE;


			if ((neighbours[0] && neighbours[2]) )
			{
				if (neighbours[0]->state != obstuction || neighbours[2]->state != obstuction)
				{
					//top-left
					neighbours.push_back(nodes[(_width * (nodeY - 1)) + (nodeX - 1)]);
				}
			}		
		


			if ((neighbours[0] && neighbours[3]) )
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
		


			if ((neighbours[1] && neighbours[3]) )
			{
				if (neighbours[1]->state != obstuction || neighbours[3]->state != obstuction)
				{
					//bottom-right
					neighbours.push_back(nodes[(_width * (nodeY + 1)) + (nodeX + 1)]);
				}
			}
		

		return neighbours;
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

