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
	NodeState modifier = NodeState::HOVER;

	switch (owner->getPhase())
	{
	case Phase::P_OBSTACLE:
		{
			modifier = NodeState::OBSTACLE;
			break;
		}
	case Phase::P_START:
		{
			modifier = NodeState::START;
			break;
		}
	case Phase::P_END:
		{
			modifier = NodeState::END;
			break;
		}
	default:
		break;
	}


	switch (evt->type)
	{
	case SDL_MOUSEMOTION:
	{
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		break;
	}
	default:
		break;
	}
}