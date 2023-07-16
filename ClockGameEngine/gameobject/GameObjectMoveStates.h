#ifndef GAMEOBJECTMOVESTATES_H_
#define GAMEOBJECTMOVESTATES_H_

enum GameObjectMoveStates : unsigned char
{
	Stopped,
	Accelerating,
	Moving,
	Decelerating,
	Ascending,
	Descending
};

#endif