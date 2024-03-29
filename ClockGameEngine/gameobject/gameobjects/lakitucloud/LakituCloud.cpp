#include "LakituCloud.h"
#include <iostream>


LakituCloud::LakituCloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : DynamicGameObject(spriteSheet, renderer, x, y)
{
}

LakituCloud::~LakituCloud()
{
}

void LakituCloud::handleEvents(BitFlag* events)
{
}

void LakituCloud::render()
{
	_renderer->drawSprite(_xPos, _yPos, _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), _spriteSheet->getSprite(39));
}

void LakituCloud::update(int frameTime)
{
	// game object update logic goes here - eg.: move game object
	/*if (_direction)
	{
		if (_hVelocity <= 1)
		{
			_hVelocity += 0.01;
		}
		_xPos += _hVelocity;
	}
	else
	{
		_xPos -= _hVelocity;
	}

	std::cout << _hVelocity << std::endl;

	if (_xPos > 100)
	{
		_direction = false;
	}

	if (_xPos <= 0)
	{
		_direction = true;
	}*/

}

