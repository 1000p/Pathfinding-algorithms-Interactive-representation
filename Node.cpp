#include "Node.h"

#include "RenderManager.h"
#include "InputManager.h"
#include "ResourceInitializer.h"


InputManager& Node::inputManager = InputManager::getInstance();
ResourceInitializer& Node::resourceInit = ResourceInitializer::getInstance();

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
			

			if (lastHovered == this && state == stateMod)
			{
				return;
			}

			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				if (owner->getEndNode())
				{
					owner->setPhase(Phase::DYNAMIC_RETRACE);
				}
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
			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				if (owner->getStartNode())
				{
					owner->setPhase(Phase::DYNAMIC_RETRACE);
				}
			}

			if (lastHovered == this && state == stateMod)
			{
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
			if (lastHovered == this && state == stateMod)
			{
				return;
			}

			bool isStartOrEnd = (permanentState == NodeState::START
				|| permanentState == NodeState::END);


			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				if (isStartOrEnd )
				{
					return;
				}	
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
				if (/*lastHovered == endNode || lastHovered == startNode ||
					lastHovered->permanentState == NodeState::OBSTACLE*/
					lastHovered->permanentState != NodeState::WHITE)
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
			Node* startNode = owner->getStartNode();
			Node* endNode = owner->getEndNode();

			if (this == startNode)
			{
				if (endNode)
				{
					endNode->changeState(endNode->memoryState);
					endNode->permanentState = endNode->memoryState;
				}
				/// <summary>
				/// START NODE CHANING TO NULL
				/// </summary>
				/// <param name="evt"></param>
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
				/// <summary>
				/// Here change of end node is happeing
				/// </summary>
				/// <param name="evt"></param>
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
			bool isStartOrEnd = permanentState == NodeState::END ||
				permanentState == NodeState::START;
	
			if (permanentState == stateMod)
			{
				if (/*this != startNode || this != endNode*/
					!isStartOrEnd)
				{
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