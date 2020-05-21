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
		Node* startNode = owner->getStartNode();
		Node* endNode = owner->getEndNode();
		switch (stateMod)
		{
		case NodeState::START:
		{	
			if (lastHovered == this && state == stateMod)
			{
				return;
			}
			
			//Else - set previous state to = last frame state
			if (this != startNode)
			{
				previousState = state;
				changeState(stateMod); // this frame state
			}
											
			
			//If there is previous hovered tile change its state back
			if (lastHovered)
			{	
				if (lastHovered == endNode || lastHovered == startNode ||
					lastHovered->permanentState == NodeState::OBSTACLE)
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
			if (lastHovered == this && state == stateMod)
			{
				return;
			}

			//Else - set previous state to = last frame state
			if (this != endNode )
			{
				previousState = state;
				changeState(stateMod); // this frame state
			}

		
			//If there is previous hovered tile change its state back
			if (lastHovered)
			{
				if (lastHovered == endNode || lastHovered == startNode ||
					lastHovered->permanentState == NodeState::OBSTACLE)
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

			bool isStartOrEnd = (lastHovered == endNode || lastHovered == startNode);


			if (inputManager.getMouseState() == SDL_MOUSEBUTTONDOWN)
			{
				if (!isStartOrEnd )
				{
					if (owner->getEraser())
					{
						permanentState = memoryState;
						changeState(memoryState);
						owner->setLastHovered(this);
						return;
					}
					permanentState = stateMod;
					changeState(stateMod);
					owner->setLastHovered(this);
					return;
				}			
			}
						
			changeState(stateMod); // this frame state
			//If there is previous hovered tile change its state back
			if (lastHovered)
			{
				if (isStartOrEnd)
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
						//lastHovered->changeState(lastHovered->memoryState);
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
				if (lastHovered == endNode || lastHovered == startNode ||
					lastHovered->permanentState == NodeState::OBSTACLE)
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
				permanentState = stateMod;
				changeState(stateMod);
				owner->setStartNode(this);
			}
			else if (this == startNode)
			{

				owner->setStartNode(nullptr);
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

			owner->setLastHovered(this);
			break;
		}
		case NodeState::OBSTACLE:
		{
			Node* startNode = owner->getStartNode();
			Node* endNode = owner->getEndNode();
	
			if (permanentState == stateMod)
			{
				if (this != startNode || this != endNode)
				{
					owner->setEraser(true);
					permanentState = memoryState;
					changeState(memoryState);
				}				
			}
			else
			{
				owner->setEraser(false);
				if (this != startNode || this != endNode)
				{
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
	case SDL_MOUSEBUTTONUP:
	{
		switch (stateMod)
		{
		case NodeState::START:
		{
			break;
		}
		case NodeState::END:
		{
			break;
		}
		case NodeState::OBSTACLE:
		{
			
			break;
		}
		case NodeState::HOVER:
		{
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