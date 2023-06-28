#include "Mario.h"
#include <iostream>

Mario::Mario(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : DynamicGameObject(spriteSheet, renderer, x, y)
{
	_maxHVelocity = 100;
	_hDeceleration = 10;
	_hAcceleration = 5;
	_maxVVelocity = 2;
	_vAcceleration = 0.07;
	_vDeceleration = 0.1;
}

Mario::~Mario()
{
}

void Mario::update(int frameTime, bool overrideX, int xOverride, bool overrideY, int yOverride)
{
	DynamicGameObject::update(frameTime, overrideX, xOverride, overrideY, yOverride);
}

void Mario::handleEvents(BitFlag* events)
{
	if (!events->HasFlag(EventTypes::ButtonLeft) && !events->HasFlag(EventTypes::ButtonRight))
	{
		_hDirection = 0;
		//std::cout << "stop" << std::endl;
	}

	if (events->HasFlag(EventTypes::ButtonLeft))
	{
		_hDirection = -1;
		//std::cout << "left" << std::endl;
	}
	else if (events->HasFlag(EventTypes::ButtonRight))
	{
		_hDirection = 1;
		//std::cout << "right" << std::endl;
	}

	if (events->HasFlag(EventTypes::ButtonUp))
	{
		_vDirection = -1;
		//std::cout << "up" << std::endl;
	}
}

void Mario::render()
{
	const int spriteWidth = _spriteSheet->spriteWidth();
	const int spriteHeight = _spriteSheet->spriteHeight();

	_renderer->drawSprite(_xPos              , _yPos               , _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), _spriteSheet->getSprite(28));
	_renderer->drawSprite(_xPos + spriteWidth, _yPos               , _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), _spriteSheet->getSprite(29));
	_renderer->drawSprite(_xPos              , _yPos + spriteHeight, _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), _spriteSheet->getSprite(42));
	_renderer->drawSprite(_xPos + spriteWidth, _yPos + spriteHeight, _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), _spriteSheet->getSprite(43));
}
