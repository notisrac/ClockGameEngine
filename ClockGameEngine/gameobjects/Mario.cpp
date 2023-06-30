#include "Mario.h"
#include <iostream>


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
		_direction = GameObjectDirection::Left;
		//std::cout << "left" << std::endl;
	}
	else if (events->HasFlag(EventTypes::ButtonRight))
	{
		_hDirection = 1;
		_direction = GameObjectDirection::Right;
		//std::cout << "right" << std::endl;
	}

	if (events->HasFlag(EventTypes::ButtonUp))
	{
		_vDirection = -1;
		_moveState = GameObjectMoveStates::Ascending;
		//std::cout << "up" << std::endl;
	}
}

void Mario::update(int frameTime)
{
	if (_hDirection != 0) // moving
	{
		_hVelocity += MARIO_H_ACELLERATION;
		_moveState = GameObjectMoveStates::Accelerating;
		if (_hVelocity >= MARIO_H_MAX_VELOCITY)
		{
			_moveState = GameObjectMoveStates::Moving;
			_hVelocity = MARIO_H_MAX_VELOCITY;

		}
		_animStep += frameTime / MARIO_ANIM_TIMING;
		//std::cout << _animStep << std::endl;
		if (_animStep > MARIO_ANIM_FRAME_COUNT)
		{
			_animStep = 0;
		}
	}

	if (_hDirection == 0)
	{
		_hVelocity -= MARIO_H_DECELERATION;
		_moveState = GameObjectMoveStates::Decelerating;
		if (_hVelocity <= 0)
		{
			_moveState = GameObjectMoveStates::Stopped;
			_hVelocity = 0;
		}
	}

	_fXPos += ((_hDirection * _hVelocity) / 1000) * frameTime;
	_xPos = round(_fXPos);

	//std::cout << _xPos << std::endl;

}


void Mario::render()
{
	switch (_moveState)
	{
		case Decelerating:
		case Stopped:
			renderMario(MARIO_SPRITE_STAND_TOPLEFT, MARIO_SPRITE_STAND_TOPRIGHT, MARIO_SPRITE_STAND_BOTTOMLEFT, MARIO_SPRITE_STAND_BOTTOMRIGHT);
			break;
		case Accelerating:
		case Moving:
			renderMarioAnim();
			break;
		case Ascending:
		case Descending:
			renderMario(MARIO_SPRITE_JUMP_TOPLEFT, MARIO_SPRITE_JUMP_TOPRIGHT, MARIO_SPRITE_JUMP_BOTTOMLEFT, MARIO_SPRITE_JUMP_BOTTOMRIGHT);
			break;
		default:
			break;
	}
}

void Mario::renderMario(unsigned char topLeft, unsigned char topRight, unsigned char bottomLeft, unsigned char bottomRight)
{
	const int spriteWidth = _spriteSheet->spriteWidth();
	const int spriteHeight = _spriteSheet->spriteHeight();

	if (_direction == GameObjectDirection::Left)
	{
		_renderer->drawSprite(_xPos              , _yPos               , spriteWidth, spriteHeight, _spriteSheet->getSprite(topRight, true));
		_renderer->drawSprite(_xPos + spriteWidth, _yPos               , spriteWidth, spriteHeight, _spriteSheet->getSprite(topLeft, true));
		_renderer->drawSprite(_xPos              , _yPos + spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(bottomRight, true));
		_renderer->drawSprite(_xPos + spriteWidth, _yPos + spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(bottomLeft, true));
	}
	else
	{
		_renderer->drawSprite(_xPos              , _yPos               , spriteWidth, spriteHeight, _spriteSheet->getSprite(topLeft));
		_renderer->drawSprite(_xPos + spriteWidth, _yPos               , spriteWidth, spriteHeight, _spriteSheet->getSprite(topRight));
		_renderer->drawSprite(_xPos              , _yPos + spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(bottomLeft));
		_renderer->drawSprite(_xPos + spriteWidth, _yPos + spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(bottomRight));
	}

}

void Mario::renderMarioAnim()
{
	std::cout << (int)_animStep * MARIO_ANIM_SPRITE_PER_FRAME << std::endl;

	renderMario(
		_runAnim[(int)_animStep * MARIO_ANIM_SPRITE_PER_FRAME + 0],
		_runAnim[(int)_animStep * MARIO_ANIM_SPRITE_PER_FRAME + 1],
		_runAnim[(int)_animStep * MARIO_ANIM_SPRITE_PER_FRAME + 2],
		_runAnim[(int)_animStep * MARIO_ANIM_SPRITE_PER_FRAME + 3]
	);

}
