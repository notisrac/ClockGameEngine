#include "DynamicGameObject.h"
#include <iostream>

DynamicGameObject::DynamicGameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : GameObject(spriteSheet, renderer, x, y)
{
}

DynamicGameObject::~DynamicGameObject()
{
}

void DynamicGameObject::update(int frameTime, bool overrideX, int xOverride, bool overrideY, int yOverride)
{
	GameObject::update(frameTime, overrideX, xOverride, overrideY, yOverride);

	if (_hDirection != 0) // moving
	{
		_hVelocity += _hAcceleration;
		if (_hVelocity >= _maxHVelocity)
		{
			_hVelocity = _maxHVelocity;
		}
	}

	if (_hDirection == 0)
	{
		_hVelocity -= _hDeceleration;
		if (_hVelocity <= 0)
		{
			_hVelocity = 0;
		}
	}

	_xPos += ((_hDirection * _hVelocity) / 1000) * frameTime;
	std::cout << _xPos << std::endl;


	//if (_vDirection > 0) // up button pressed
	//{
	//	if (_vVelocity == 0) // on the ground
	//	{
	//		_vVelocity = _maxVVelocity;
	//	}
	//}

}
