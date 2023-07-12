#pragma once
#include <iostream>

#include "GameObject.h"
#include "GameObjectMoveStates.h"

class DynamicGameObject : public GameObject
{
public:
	DynamicGameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : GameObject(spriteSheet, renderer, x, y)
	{
		_fXPos = x;
		_fYPos = y;
	}
	~DynamicGameObject() {}

	// Inherited via GameObject
	//virtual void handleEvents(BitFlag* events) override = 0;
	//virtual void update(int frameTime) override = 0;
	//virtual void render() override = 0;
	virtual void setPosition(int x, int y, bool displayOnly = true)
	{
		//std::cout << "x: " << x << " xpos: " << _xPos << " fxpos: " << _fXPos << " fract: " << (_xPos - _fXPos) << " new fxpos: " << x + (_xPos - _fXPos) << std::endl;
		GameObject::setPosition(x, y);
		if (!displayOnly)
		{
			//_fXPos = x + (_xPos - _fXPos);
			//_fYPos = y + (_yPos - _fYPos);
			_fXPos = x;
			_fYPos = y;
		}
	}


protected:
	//GameObjectMoveStates _moveState = GameObjectMoveStates::Stopped;
	char _hDirection = 0;
	char _vDirection = 0;
	float _fXPos = 0;
	float _fYPos = 0;
	float _hVelocity = 0;
	float _vVelocity = 0;
};

