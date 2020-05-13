#include "Node.h"

#include "RenderManager.h"
#include "InputManager.h"
#include "ResourceInitializer.h"


InputManager& Node::inputManager = InputManager::getInstance();
ResourceInitializer& Node::resourceInit = ResourceInitializer::getInstance();
/*
SDL_Texture* Node::openT = nullptr;
SDL_Texture* Node::closedT = nullptr;
SDL_Texture* Node::startT = nullptr;
SDL_Texture* Node::endT = nullptr;
SDL_Texture* Node::pathT = nullptr;
SDL_Texture* Node::obstacleT = nullptr;
SDL_Texture* Node::whiteT = nullptr;
SDL_Texture* Node::hoverT = nullptr;
*/

void Node::changeState(NodeState newState)
{
	state = newState;

	texture = resourceInit.getTexture(state);

	/*
	switch (state)
	{
	case NodeState::CLOSED:
	{
	texture = closedT;
	break;
	}
	case NodeState::OPEN:
	{
	texture = openT;
	break;
	}
	case NodeState::END:
	{
	texture = endT;
	break;
	}
	case NodeState::START:
	{
	texture = startT;
	break;
	}
	case NodeState::OBSTACLE:
	{
	texture = obstacleT;
	break;
	}
	case NodeState::WHITE:
	{
	//if (texture == obstacleT)
	//{
	//	return;
	//}
	texture = whiteT;
	break;
	}
	case NodeState::PATH:
	{
	texture = pathT;
	break;
	}
	case NodeState::HOVER:
	{
	/*if (texture == obstacleT)
	{
	return;
	}
	texture = hoverT;
	break;
	}
	default:
	{
	//TODO: ADD TERMINATE PROGRAM FUNCTION RETURNING ERROR MSG
	texture = nullptr;
	break;
	}
	}
	*/
}

/*
void Node::initializeNodeTextures()
{

	SDL_Renderer* renderer = RenderManager::getRenderer();

	//SDL_ShowWindow(RenderManager::getWindow());

	//Check if textures are initialized
	if (openT != nullptr || closedT != nullptr || startT != nullptr ||
		endT != nullptr || pathT != nullptr || obstacleT != nullptr ||
		whiteT != nullptr)
	{
		std::cout << "Textures already initialized!" << std::endl;
		return;
	}

	//Load surfaces from files
	SDL_Surface* open = IMG_Load("Tiles/opened.png");
	SDL_Surface* close = IMG_Load("Tiles/closed.png");
	SDL_Surface* start = IMG_Load("Tiles/start.png");
	SDL_Surface* end = IMG_Load("Tiles/end.png");
	SDL_Surface* path = IMG_Load("Tiles/path.png");
	SDL_Surface* obstacle = IMG_Load("Tiles/obstacle.png");
	SDL_Surface* white = IMG_Load("Tiles/white.png");
	SDL_Surface* hover = IMG_Load("Tiles/hover.png");

	//If any surface is not initialized exit
	if (open == nullptr || close == nullptr || start == nullptr ||
		end == nullptr || path == nullptr || obstacle == nullptr ||
		white == nullptr || hover == nullptr)
	{
		std::cout << "Could not load tile/s surfaces!" << std::endl;
		exit(-404);
	}

	//TEST
	SDL_RenderClear(renderer);

	//Create textures from surfaces and global renderer
	openT = SDL_CreateTextureFromSurface(renderer, open);
	closedT = SDL_CreateTextureFromSurface(renderer, close);
	startT = SDL_CreateTextureFromSurface(renderer, start);
	endT = SDL_CreateTextureFromSurface(renderer, end);
	pathT = SDL_CreateTextureFromSurface(renderer, path);
	obstacleT = SDL_CreateTextureFromSurface(renderer, obstacle);
	whiteT = SDL_CreateTextureFromSurface(renderer, white);
	hoverT = SDL_CreateTextureFromSurface(renderer, hover);

	/*
	SDL_ShowWindow(RenderManager::getWindow());
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, hoverT, NULL, NULL);
	SDL_RenderPresent(renderer);
	

	//If any texture is not initialized exit
	if (openT == nullptr || closedT == nullptr || startT == nullptr ||
		endT == nullptr || pathT == nullptr || obstacleT == nullptr ||
		whiteT == nullptr || hoverT == nullptr)
	{
		std::cout << "Could not load tile/s textures from surfaces!" << std::endl;
		exit(-404);
	}
	//Release resources
	SDL_FreeSurface(open);
	SDL_FreeSurface(close);
	SDL_FreeSurface(start);
	SDL_FreeSurface(end);
	SDL_FreeSurface(path);
	SDL_FreeSurface(obstacle);
	SDL_FreeSurface(white);
	SDL_FreeSurface(hover);

}
*/
void Node::handleEvent (SDL_Event* evt)
{
	NodeState modifier = NodeState::WHITE;

	//Checks the event type
	switch (evt->type)
	{
		//if it's motion
	case SDL_MOUSEMOTION:
	{
		//Switch on mouse state held down or not
		switch (inputManager.getMouseState())
		{
			//Mouse held down
		case SDL_MOUSEBUTTONDOWN:
		{
			//Get different texture based on phase
			switch (owner->getPhase())
			{
				//Obstacle drawing phase
			case Phase::P_OBSTACLE:
			{			
				if (owner->getEraser())
				{
					modifier = NodeState::WHITE;
				}
				else 
				{
					modifier = NodeState::OBSTACLE;
				}
				
				break;
			}
			default:
				break;
			}
			break;
		}
		 //Mouse button not held down
		case SDL_MOUSEBUTTONUP:
		{
			//Get last hovered tile and check if it's tile is obstacle
			Node* lastHovered = owner->getLastHovered();
			if (lastHovered && lastHovered->state != NodeState::OBSTACLE)
			{
				//If not obstacle change to white
				lastHovered->changeState(NodeState::WHITE);		
				//Else do nothing
			}
			//Check if this tile is obstacle
			if (state != NodeState::OBSTACLE) // If not obstacle
			{
				modifier = NodeState::HOVER; // Change to Hover
			}
			else // It is obstacle 
			{
				modifier = NodeState::OBSTACLE; //keep it obstacle
			}
			owner->setLastHovered(this);
			break;
		}
		default:
			break;
		}

		break;
	}

	//Single click event
	case SDL_MOUSEBUTTONDOWN:
	{ 
		//If this is obstacle
		if (texture == resourceInit.getTexture(NodeState::OBSTACLE))
		{
			modifier = NodeState::WHITE; //Return to empty tile
			owner->setEraser(true);
			break;
		}
		//else keep obstacle
		modifier = NodeState::OBSTACLE;
		owner->setEraser(false);
		break;
	}
	default:
		break;
	}

	//Change tile based on modifier;
	changeState(modifier);
}
