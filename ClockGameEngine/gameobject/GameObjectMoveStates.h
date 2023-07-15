#pragma once

enum GameObjectMoveStates : unsigned char
{
	Stopped,
	Accelerating,
	Moving,
	Decelerating,
	Ascending,
	Descending
};