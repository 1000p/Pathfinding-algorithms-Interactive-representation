#pragma once

//Defines different state that a node can be in
//It is used when we change the node state
//Or when we need a new texture for that node from the resource initializer
enum class NodeState
{
	OPEN,
	CLOSED,
	START,
	END,
	PATH,
	OBSTACLE,
	WHITE,
	HOVER,
	DEFAULT
};