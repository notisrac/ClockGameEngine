#pragma once
#include <stdexcept>

#include "Renderer.h"
#include "SpriteSheet.h"

class GameObject
{
public:
	GameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~GameObject();

	virtual void handleEvents(BitFlag* events) = 0;

	// game object update logic goes here - eg.: move game object
	virtual void update(int frameTime, bool overrideX = false, int xOverride = 0, bool overrideY = false, int yOverride = 0)
	{
		_frameTime = frameTime;
		if (overrideX)
		{
			_xPos = xOverride;
		}
		if (overrideY)
		{
			_yPos = yOverride;
		}
	}

	virtual void render() = 0;
// sample implementation
//	int* pixels = _spriteSheet->getSprite(39);
//	_renderer->drawSprite(_xPos, _yPos, _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), pixels);

protected:
	SpriteSheet* _spriteSheet;
	Renderer* _renderer;
	float _xPos;
	float _yPos;
	int _frameTime = 0;
};
