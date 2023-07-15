#pragma once
#include <iostream>

#include "GameObject.h"
#include "GameObjectMoveStates.h"

class DynamicGameObject : public GameObject
{
public:
	DynamicGameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : GameObject(spriteSheet, renderer, x, y)
	{
		_fXPos = (float)x;
		_fYPos = (float)y;
	}
	~DynamicGameObject() {}

	// Inherited via GameObject
	virtual void setPosition(int x, int y, bool displayOnly = true)
	{
		GameObject::setPosition(x, y);
		if (!displayOnly)
		{
			_fXPos = (float)x;
			_fYPos = (float)y;
		}
	}


protected:
	char _hDirection = 0;
	char _vDirection = 0;
	float _fXPos = 0;
	float _fYPos = 0;
	float _hVelocity = 0;
	float _vVelocity = 0;
};

