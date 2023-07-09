#pragma once
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

protected:
	//GameObjectMoveStates _moveState = GameObjectMoveStates::Stopped;
	char _hDirection = 0;
	char _vDirection = 0;
	float _fXPos = 0;
	float _fYPos = 0;
	float _hVelocity = 0;
	float _vVelocity = 0;
};

