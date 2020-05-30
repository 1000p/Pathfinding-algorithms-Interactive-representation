#pragma once
#include "NodesMap.h"

#include <unordered_set>
#include <queue>
#include <algorithm>

class AStarPathfinder
{
public:

	void findPath(Node* start, Node* target)
	{
		std::list<Node*> openNodes;
		NodeState startMemoryState = start->memoryState;
		NodeState targetMemoryState = target->memoryState;

		openNodes.push_back(start);

		while (!openNodes.empty())
		{
			Node* current = openNodes.front();

			std::list<Node*>::iterator beg = openNodes.begin();
			std::list<Node*>::iterator end = openNodes.end();
			for (; beg != end; ++beg)
			{
				int begFcost = (*beg)->Fcost();
				int currentFcost = current->Fcost();
				if (begFcost < currentFcost ||
					(begFcost == currentFcost &&
						(*beg)->Hcost < current->Hcost))
				{
					current = (*beg);
				}
			}
				openNodes.remove(current);
				current->memoryState = current->permanentState;
				current->changeState(NodeState::CLOSED);
				current->permanentState = current->state;
				

				if (current == target)
				{
					//RETURN WHAT ?? INDICATE VIA POINTER
					retracePath(current, start);
					start->changeState(NodeState::START);
					start->permanentState = start->state;
					start->memoryState = startMemoryState;
					target->changeState(NodeState::END);
					target->permanentState = target->state;
					target->memoryState = targetMemoryState;
					target->owner->setPhase(Phase::PATH_FOUND);
					return;
				}

				
				for (auto neighbour : current->owner->getNeighbours(current))
				{
					if (neighbour)
					{
						if (neighbour->state != NodeState::OBSTACLE &&
							neighbour->state != NodeState::CLOSED)
						{
							int costToNeighbour =
								current->Gcost + getDistance(current, neighbour);
							bool NotInOpen = neighbour->state != NodeState::OPEN;

							if (costToNeighbour < neighbour->Gcost ||
								NotInOpen)
							{
								neighbour->Gcost = costToNeighbour;
								neighbour->Hcost = getDistance(neighbour, target);
								neighbour->pathParrent = current;

								if (NotInOpen)
								{
									openNodes.push_back(neighbour);
									neighbour->memoryState = neighbour->permanentState;
									neighbour->changeState(NodeState::OPEN);
									neighbour->permanentState = neighbour->state;
								}
							}

						}
					}
					
				}

			
		}	
	}

private:

	int getDistance(Node* nodeA, Node* nodeB)
	{
		int distX = abs(nodeA->x - nodeB->x);
		int distY = abs(nodeA->y - nodeB->y);

		return (distX > distY ? 14 * distY + 10 * (distX - distY) :
			14 * distX + 10 * (distY - distX));
	}

	void retracePath(Node* from, Node* to)
	{
		while (from->pathParrent != to)
		{
			from->pathParrent->changeState(NodeState::PATH);
			from->pathParrent->permanentState = from->pathParrent->state;
			from = from->pathParrent;
		}
	}
};

