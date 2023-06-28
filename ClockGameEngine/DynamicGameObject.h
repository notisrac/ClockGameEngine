#pragma once
#include "GameObject.h"
#include "GameObjectMoveStates.h"

class DynamicGameObject : public GameObject
{
public:
	DynamicGameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~DynamicGameObject();

	void update(int frameTime, bool overrideX = false, int xOverride = 0, bool overrideY = false, int yOverride = 0) override;


	// Inherited via GameObject
	//virtual void handleEvents(BitFlag* events) override;

	//virtual void render() override;

	//void update(int frameTime);

protected:
	GameObjectMoveStates _moveState = GameObjectMoveStates::Stopped;
	char _hDirection = 0;
	char _vDirection = 0;
	float _vVelocity = 0;
	float _hVelocity = 0;
	float _maxHVelocity = 0;
	float _hDeceleration = 0;
	float _hAcceleration = 0;
	float _maxVVelocity = 0;
	float _vAcceleration = 0;
	float _vDeceleration = 0;
};

