#pragma once

#include "PathAlgorithm.h"
class Node;

class AStarPathfinder: public PathAlgorithm
{
public:

	virtual ~AStarPathfinder() = default;

	virtual void findPath(Node* start, Node* target, bool delay,
		SDL_Renderer* renderer, SDL_Texture* renderTarget) override;

private:

	//Gets the distance between two nodes
	int getDistance(Node* nodeA, Node* nodeB);

	//Retraces the path back from the target to the start and changes its state
	void retracePath(Node* from, Node* to);

	int delayInMiliseconds;
};

