#pragma once

//Defines the nodes map current phase
enum class Phase
{
	PATH_FOUND,
	NO_PATH,
	NO_START_OR_END,
	CAN_CALCULATE_PATH,
	DYNAMIC_RETRACE,
	DEFAULT
};