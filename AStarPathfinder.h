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

	int getDistance(Node* nodeA, Node* nodeB);

	void retracePath(Node* from, Node* to);

	int delayInMiliseconds;
};

