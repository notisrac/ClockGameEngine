#include "Cloud.h"
#include <iostream>


Cloud::Cloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : DynamicGameObject(spriteSheet, renderer, x, y)
{
}

void Cloud::update(int frameTime, bool overrideX, int xOverride, bool overrideY, int yOverride)
{
	GameObject::update(frameTime);
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

void Cloud::render()
{
	int* pixels = _spriteSheet->getSprite(39);
	_renderer->drawSprite(_xPos, _yPos, _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), pixels);
}

void Cloud::handleEvents(BitFlag* events)
{
}
