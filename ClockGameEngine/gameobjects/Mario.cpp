#include "Mario.h"
#include <iostream>

#define MARIO_H_MAX_VELOCITY 100
#define MARIO_H_ACELLERATION 5
#define MARIO_H_DECELERATION 10
#define MARIO_V_MAX_VELOCITY 100
#define MARIO_V_ACELLERATION 100
#define MARIO_V_DECELERATION 100

Mario::Mario(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y) : DynamicGameObject(spriteSheet, renderer, x, y)
{
}

Mario::~Mario()
{
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

void Mario::update(int frameTime)
{
	if (_hDirection != 0) // moving
	{
		_hVelocity += MARIO_H_ACELLERATION;
		if (_hVelocity >= MARIO_H_MAX_VELOCITY)
		{
			_hVelocity = MARIO_H_MAX_VELOCITY;
		}
	}

	if (_hDirection == 0)
	{
		_hVelocity -= MARIO_H_DECELERATION;
		if (_hVelocity <= 0)
		{
			_hVelocity = 0;
		}
	}

	_fXPos += ((_hDirection * _hVelocity) / 1000) * frameTime;
	_xPos = round(_fXPos);

	std::cout << _xPos << std::endl;

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
