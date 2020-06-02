#include "AStarPathfinder.h"

#include "Node.h"
#include "NodesMap.h"
#include "PhaseDefines.h"

#include <unordered_set>
#include <queue>
#include <algorithm>

void AStarPathfinder::findPath(Node* start, Node* target, bool delay,
	SDL_Renderer* renderer, SDL_Texture* renderTarget)
{
	//To store opened nodes
	std::list<Node*> openNodes;
	//To keep the previous start/end memory state
	NodeState startMemoryState = start->memoryState;
	NodeState targetMemoryState = target->memoryState;

	//Add start node to opened nodes
	openNodes.push_back(start);

	//While we have opened nodes continue
	while (!openNodes.empty())
	{
		//The current node that we will work with
		Node* current = openNodes.front();

		//Iterate true the opened nodes to find the 
		//one with the best path cost
		std::list<Node*>::iterator beg = openNodes.begin();
		std::list<Node*>::iterator end = openNodes.end();
		for (; beg != end; ++beg)
		{
			int begFcost = (*beg)->Fcost();
			int currentFcost = current->Fcost();

			//If the F cost is less or F cost is == to other F cost
			// and H cost is less then other - make current the this node
			if (begFcost < currentFcost ||
				(begFcost == currentFcost &&
					(*beg)->Hcost < current->Hcost))
			{
				current = (*beg);
			}
		}
		//Remove the current node from opened nodes and change its states
		openNodes.remove(current);
		current->memoryState = current->permanentState;
		current->changeState(NodeState::CLOSED);
		current->permanentState = current->state;

		if (delay)
		{
			current->owner->render(renderer, renderTarget);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}

		//If current is target we arrived to our destination
		if (current == target)
		{
			//Retrace the path - change its appearence
			retracePath(current, start);
			//In order to keep start/end appearance and states
			start->changeState(NodeState::START);
			start->permanentState = start->state;
			start->memoryState = startMemoryState;
			target->changeState(NodeState::END);
			target->permanentState = target->state;
			target->memoryState = targetMemoryState;
			target->owner->setPhase(Phase::PATH_FOUND);

			return;
		}

		//Get the current node neighbours and iterate 
		for (auto neighbour : current->owner->getNeighbours(current))
		{
			//getNeighbours can return nullptr (to avoid diagonal moves)
			if (neighbour)
			{
				//If neighbour is not obstacle or its closed 
				if (neighbour->permanentState != NodeState::OBSTACLE &&
					neighbour->permanentState != NodeState::CLOSED)
				{
					//Calculate cost to neighbour from current
					int costToNeighbour =
						current->Gcost + getDistance(current, neighbour);
					//If its not already opened 
					bool NotInOpen = neighbour->state != NodeState::OPEN;

					//Path cost is less or its not opened
					if (costToNeighbour < neighbour->Gcost ||
						NotInOpen)
					{
						//Set the G and H cost and the path parrent
						neighbour->Gcost = costToNeighbour;
						neighbour->Hcost = getDistance(neighbour, target);
						neighbour->pathParrent = current;

						//If not in opened list add to open and change states
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
	//We did not found a path
	//Change the start/end node states back 
	//Set map phase to a no path scenario
	start->changeState(NodeState::START);
	start->permanentState = start->state;
	start->memoryState = startMemoryState;
	target->changeState(NodeState::END);
	target->permanentState = target->state;
	target->memoryState = targetMemoryState;
	target->owner->setPhase(Phase::NO_PATH);
}

//Gets the distance between two nodes
int AStarPathfinder::getDistance(Node* nodeA, Node* nodeB)
{
	int distX = abs(nodeA->x - nodeB->x);
	int distY = abs(nodeA->y - nodeB->y);

	return (distX > distY ? 14 * distY + 10 * (distX - distY) :
		14 * distX + 10 * (distY - distX));
}

//Retraces the path back from the target to the start and changes its state
void AStarPathfinder::retracePath(Node* from, Node* to)
{
	while (from->pathParrent != to)
	{
		from->pathParrent->changeState(NodeState::PATH);
		from->pathParrent->permanentState = from->pathParrent->state;
		from = from->pathParrent;
	}
}
