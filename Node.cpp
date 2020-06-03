#include "Node.h"
#include "NodesMap.h"

#include "ResourceInitializer.h"
#include "InputManager.h"

InputManager& Node::inputManager = InputManager::getInstance();
ResourceInitializer& Node::resourceInit = ResourceInitializer::getInstance();

Node::Node(NodeState state, int y, int x, NodesMap* owner)
	:texture(nullptr), owner(owner), state(state), previousState(state), memoryState(state),
	permanentState(state), pathParrent(nullptr), x(x), y(y), Gcost(0), Hcost(0) {
	changeState(state);
}

//Changes the state and its appearance/texture accordingly
void Node::changeState(NodeState newState)
{
	state = newState;

	texture = resourceInit.getTexture(state);

}


void Node::handleEvent(SDL_Event* evt)
{
	NodeState stateMod = owner->getDrawTile();
	Node* lastHovered = owner->getLastHovered();	
	SDL_Texture* tileMod = resourceInit.getTexture(stateMod);

	switch (evt->type)
	{
	case SDL_MOUSEMOTION:
	{

		switch (stateMod)
		{
		case NodeState::START:
		{	
			//If this is not the last hovered node 
			//a.k.a we are still in the same node
			// and its state is not == to the state to be 
			if (lastHovered == this && state == stateMod)
			{
				return;
			}
			//If the mouse button is held down we should try to 
			//dynamically calculate the path depending on its phase
			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				handleMapPhase(stateMod);
				return;
			}
			
			
			previousState = state;
			changeState(stateMod); // this frame state
								
			//If there is previous hovered tile change its state back
			if (lastHovered)
			{	
				if (lastHovered->permanentState != NodeState::WHITE)
				{
					if (this != lastHovered)
					{
						lastHovered->changeState(lastHovered->permanentState);
					}
					
				}
				else
				{
					if (this != lastHovered)
					{
						lastHovered->changeState(lastHovered->memoryState);
					}
				}
			}
			//Set this to be the last hovered tile
			owner->setLastHovered(this);
			break;
		}
		case NodeState::END:
		{
			//If this is not the last hovered node 
			//a.k.a we are still in the same node
			// and its state is not == to the state to be 
			if (lastHovered == this && state == stateMod)
			{
				return;
			}
			//If the mouse button is held down we should try to 
			//dynamically calculate the path depending on its phase
			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				handleMapPhase(stateMod);
				return;
			}
			

				previousState = state;
				changeState(stateMod); // this frame state

			//If there is previous hovered tile change its state back
			if (lastHovered)
			{
				if (lastHovered->permanentState != NodeState::WHITE)
				{
					if (this != lastHovered)
					{
						lastHovered->changeState(lastHovered->permanentState);
					}
				}
				else
				{
					if (this != lastHovered )
					{
						lastHovered->changeState(lastHovered->memoryState);
					}
				}

			}
			//Set this to be the last hovered tile
			owner->setLastHovered(this);
			break;
		}
		case NodeState::OBSTACLE:
		{
			//If this is not the last hovered node 
			//a.k.a we are still in the same node
			// and its state is not == to the state to be 
			if (lastHovered == this && state == stateMod)
			{
				return;
			}

			bool isStartOrEnd = (permanentState == NodeState::START
				|| permanentState == NodeState::END);

			//If the mouse button is held down
			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				//If its start or end we dont want to do anything
				if (isStartOrEnd )
				{
					return;
				}				
				
				//If the eraser is active a.k.a we clicked on a obstacle tile
				// now we can "delete" obstacles
				if (owner->getEraser())
				{
					if (permanentState == NodeState::OBSTACLE)
					{
						permanentState = memoryState;
						changeState(memoryState);
						owner->setLastHovered(this);						
					}	
					return;
				}
				//If this state is not blank/white try to react based on 
				//map phase
				if (permanentState != NodeState::WHITE)
				{
					handleMapPhase(stateMod);
				}

				//Else no eraser 
				if (permanentState != stateMod)
				{
					memoryState = permanentState;
				}				
				permanentState = stateMod;
				
				changeState(stateMod);
				owner->setLastHovered(this);
				return;
			}
			
			
			changeState(stateMod); // this frame state
			//If there is previous hovered tile change its state back
			if (lastHovered)
			{
				if (lastHovered->permanentState != NodeState::WHITE)
				{
					if (this != lastHovered)
					{
						lastHovered->changeState(lastHovered->permanentState);
					}
				}
				else
				{
					if (this != lastHovered)
					{
						if (lastHovered->permanentState != stateMod)
						{
							lastHovered->changeState(lastHovered->memoryState);
						}
					}
				}

			}
			//Set this to be the last hovered tile
			owner->setLastHovered(this);
			break;
		}
		case NodeState::HOVER:
		{
			if (lastHovered == this && state == stateMod)
			{
				return;
			}

			changeState(stateMod); // this frame state
			//If there is previous hovered tile change its state back
			if (lastHovered)
			{
				if (lastHovered->permanentState != NodeState::WHITE)
				{
					if (this != lastHovered)
					{
						lastHovered->changeState(lastHovered->permanentState);
					}
				}
				else
				{
					if (this != lastHovered)
					{
						lastHovered->changeState(lastHovered->memoryState);
					}
				}

			}
			//Set this to be the last hovered tile
			owner->setLastHovered(this);
			break;
		}
		default:
			break;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		switch (stateMod)
		{
		case NodeState::START:
		{
			//If this node is start node remove start node and make it nullptr
			//If this node is end node remove end node(nullptr)
			//and make this node start
			//If not end or start set as start node
			Node* startNode = owner->getStartNode();
			Node* endNode = owner->getEndNode();

			if (this == endNode)
			{
				if (startNode)
				{
					startNode->changeState(startNode->memoryState);
					startNode->permanentState = startNode->memoryState;
				}
				owner->setEndNode(nullptr);
				endNode = nullptr;
				permanentState = stateMod;
				changeState(stateMod);
				owner->setStartNode(this);
			}
			else if (this == startNode)
			{

				owner->setStartNode(nullptr);
				startNode = nullptr;
				permanentState = memoryState;
				changeState(permanentState);
			}
			else
			{
				memoryState = permanentState;
				if (startNode)
				{
					startNode->changeState(startNode->memoryState);
					startNode->permanentState = startNode->memoryState;
				}
				owner->setStartNode(this);				
				changeState(stateMod);
				permanentState = stateMod;
				startNode = this;
			}

			if (startNode == nullptr || endNode == nullptr)
			{
				owner->setPhase(Phase::NO_START_OR_END);
			}
			else
			{
				owner->setPhase(Phase::CAN_CALCULATE_PATH);
			}

			owner->setLastHovered(this);
			break;
		}
		case NodeState::END:
		{
			//Read comment in the begging at the SAME CASE FOR START 
			Node* startNode = owner->getStartNode();
			Node* endNode = owner->getEndNode();

			if (this == startNode)
			{
				if (endNode)
				{
					endNode->changeState(endNode->memoryState);
					endNode->permanentState = endNode->memoryState;
				}
				startNode = nullptr;
				owner->setStartNode(nullptr);
				permanentState = stateMod;
				changeState(stateMod);
				owner->setEndNode(this);
			}
			else if (this == endNode)
			{
				owner->setEndNode(nullptr);
				permanentState = memoryState;
				changeState(permanentState);
				endNode = nullptr;
			}
			else
			{
				memoryState = permanentState;
				if (endNode)
				{
					endNode->changeState(endNode->memoryState);
					endNode->permanentState = endNode->memoryState;
				}
				owner->setEndNode(this);
				changeState(stateMod);
				permanentState = stateMod;
				endNode = this;
			}

			if (startNode == nullptr || endNode == nullptr)
			{
				owner->setPhase(Phase::NO_START_OR_END);
			}
			else
			{
				owner->setPhase(Phase::CAN_CALCULATE_PATH);
			}

			owner->setLastHovered(this);
			break;
		}
		case NodeState::OBSTACLE:
		{
			//If this is start or end we do nothing
			//If this is obstacle we set our eraser to true - allowing us to "delete"
			//obstacles on mouse hover
			//If this is not obstacle set eraser to false and make this obstacle
			bool isStartOrEnd = permanentState == NodeState::END ||
				permanentState == NodeState::START;
	
			if (permanentState == stateMod)
			{
				if (!isStartOrEnd)
				{
					handleMapPhase(stateMod);
					owner->setEraser(true);
					permanentState = memoryState;
					changeState(memoryState);
				}				
			}
			else
			{
				owner->setEraser(false);
				if (!isStartOrEnd)
				{	
					if (permanentState != NodeState::WHITE)
					{
						handleMapPhase(stateMod);
					}
					memoryState = permanentState;
					permanentState = stateMod;
					changeState(stateMod);
				}
			}
			
			
			//Set this to be the last hovered tile
			
			owner->setLastHovered(this);
			break;
		}
		default:
			break;
		}
		break;
	}
	
	default:
		break;
	}

	
}

void Node::handleMapPhase(NodeState tileState)
{
	//function is set to be a NodesMap member function pointer
	typedef void (NodesMap::* setStartOrEndFN)(Node* node);
	setStartOrEndFN function = nullptr; {}
	switch (tileState)
	{
		//If start or end we create a "fake" event and use this handleEvent function
		//To change start or end accordinglly
	case NodeState::START:
	{
		function = &NodesMap::setStartNode;
		SDL_Event checkIfEnd;
		checkIfEnd.type = SDL_MOUSEBUTTONDOWN;
		handleEvent(&checkIfEnd);
		break;
	}

	case NodeState::END:
	{
		function = &NodesMap::setEndNode;
		SDL_Event checkIfEnd;
		checkIfEnd.type = SDL_MOUSEBUTTONDOWN;
		handleEvent(&checkIfEnd);
		break;
	}
	//If obstacle and there is already a path 
	//Or there is no path 
	// We should recalculate the path when removing/adding this obstacle 
	//It is done every frame so it will have a drastic inpact on performance
	case NodeState::OBSTACLE:
	{

		Phase mapPhase = owner->getPhase();
		if (mapPhase == Phase::PATH_FOUND ||
			mapPhase == Phase::NO_PATH)
		{
			owner->setPhase(Phase::CAN_CALCULATE_PATH);
		}
		//Return because following is obsolete for obstacle
		return;

	}
	default:
		break;
	}

	switch (owner->getPhase())
	{
	case Phase::CAN_CALCULATE_PATH:
	{
		(owner->*function)(this);
		owner->setPhase(Phase::CAN_CALCULATE_PATH);
		break;
	}
	case Phase::PATH_FOUND:
	{
		(owner->*function)(this);
		owner->setPhase(Phase::CAN_CALCULATE_PATH);
		break;
	}
	case Phase::NO_START_OR_END:
	{
		(owner->*function)(this);
		if (owner->getStartNode() && owner->getEndNode())
		{
			owner->setPhase(Phase::CAN_CALCULATE_PATH);
			handleMapPhase(tileState);
		}
		break;
	}
	default:
		break;
	}
}



int Node::getX() const
{
	return x;
}

int Node::getY() const
{
	return y;
}

int Node::Fcost()
{
	return Gcost + Hcost;
}
