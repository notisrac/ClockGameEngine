#include "Cloud.h"

Cloud::Cloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y, int speed, int maxDistance) : DynamicGameObject(spriteSheet, renderer, x, y)
{
	_speed = speed;
	_maxDistance = maxDistance;
}

Cloud::~Cloud()
{
}


void Cloud::handleEvents(BitFlag* events)
{
}

void Cloud::update(int frameTime)
{
	if (_speed != 0)
	{
		_xPosDelta += ((float)_speed / 1000) * frameTime;

		if (abs(_xPosDelta) > _maxDistance)
		{ // loop around
			_xPosDelta = -1 * _xPosDelta;
		}
	}
	//std::cout << "x: " << _xPos << " (" << _fXPos << ", " << _xPosDelta << ")" << std::endl;
}

void Cloud::render()
{
	//std::cout << "x: " << _xPos << " (" << _fXPos << ", " << _xPosDelta << ")" << std::endl;
	_xPos += round(_xPosDelta);

	// top row
	_renderer->drawSprite(_xPos                                  , _yPos                               , _spriteSheet->spriteWidth(), _spriteSheet->spriteHeight(), _spriteSheet->getSprite(9));
	_renderer->drawSprite(_xPos + _spriteSheet->spriteWidth()    , _yPos                               , _spriteSheet->spriteWidth(), _spriteSheet->spriteHeight(), _spriteSheet->getSprite(10));
	_renderer->drawSprite(_xPos + 2 * _spriteSheet->spriteWidth(), _yPos                               , _spriteSheet->spriteWidth(), _spriteSheet->spriteHeight(), _spriteSheet->getSprite(11));
	// bottom row 
	_renderer->drawSprite(_xPos                                  , _yPos + _spriteSheet->spriteHeight(), _spriteSheet->spriteWidth(), _spriteSheet->spriteHeight(), _spriteSheet->getSprite(23));
	_renderer->drawSprite(_xPos + _spriteSheet->spriteWidth()    , _yPos + _spriteSheet->spriteHeight(), _spriteSheet->spriteWidth(), _spriteSheet->spriteHeight(), _spriteSheet->getSprite(24));
	_renderer->drawSprite(_xPos + 2 * _spriteSheet->spriteWidth(), _yPos + _spriteSheet->spriteHeight(), _spriteSheet->spriteWidth(), _spriteSheet->spriteHeight(), _spriteSheet->getSprite(25));
}
