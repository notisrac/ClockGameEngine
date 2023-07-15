#pragma once
#include "../../DynamicGameObject.h"
#include "../../GameObjectDirection.h"

#define MARIO_H_MAX_VELOCITY 100
#define MARIO_H_ACELLERATION 10
#define MARIO_H_DECELERATION 10
#define MARIO_V_MAX_VELOCITY 100
#define MARIO_V_ACELLERATION 5
#define MARIO_V_DECELERATION 4.5
#define MARIO_V_MAX_HEIGHT 50

#define MARIO_ANIM_TIMING 100.0
#define MARIO_ANIM_FRAME_COUNT 3
#define MARIO_ANIM_SPRITE_PER_FRAME 4

#define MARIO_SPRITE_STAND_TOPLEFT 28
#define MARIO_SPRITE_STAND_TOPRIGHT 29
#define MARIO_SPRITE_STAND_BOTTOMLEFT 42
#define MARIO_SPRITE_STAND_BOTTOMRIGHT 43

#define MARIO_SPRITE_JUMP_TOPLEFT 30
#define MARIO_SPRITE_JUMP_TOPRIGHT 31
#define MARIO_SPRITE_JUMP_BOTTOMLEFT 44
#define MARIO_SPRITE_JUMP_BOTTOMRIGHT 45

#define MARIO_SPRITE_RUN_1_TOPLEFT 32
#define MARIO_SPRITE_RUN_1_TOPRIGHT 33
#define MARIO_SPRITE_RUN_1_BOTTOMLEFT 46
#define MARIO_SPRITE_RUN_1_BOTTOMRIGHT 47

#define MARIO_SPRITE_RUN_2_TOPLEFT 34
#define MARIO_SPRITE_RUN_2_TOPRIGHT 35
#define MARIO_SPRITE_RUN_2_BOTTOMLEFT 48
#define MARIO_SPRITE_RUN_2_BOTTOMRIGHT 49

#define MARIO_SPRITE_RUN_3_TOPLEFT 36
#define MARIO_SPRITE_RUN_3_TOPRIGHT 37
#define MARIO_SPRITE_RUN_3_BOTTOMLEFT 50
#define MARIO_SPRITE_RUN_3_BOTTOMRIGHT 51

class Mario : public DynamicGameObject
{
public:
	Mario(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~Mario();

	// Inherited via DynamicGameObject
	virtual void handleEvents(BitFlag* events) override;
	virtual void update(int frameTime) override;
	virtual void render() override;
	virtual int getWidth() override
	{
		return _spriteSheet->spriteWidth() * 2;
	}
	virtual int getHeight() override
	{
		return _spriteSheet->spriteHeight() * 2;
	}

protected:
	void renderMario(unsigned char topLeft, unsigned char topRight, unsigned char bottomLeft, unsigned char bottomRight);
	void renderMarioAnim();
	GameObjectMoveStates _moveState = GameObjectMoveStates::Stopped;
	GameObjectDirection _direction = GameObjectDirection::Right;
	float _animStep = 0.0;
	const int _runAnim[12]{
		MARIO_SPRITE_RUN_2_TOPLEFT,
		MARIO_SPRITE_RUN_2_TOPRIGHT,
		MARIO_SPRITE_RUN_2_BOTTOMLEFT,
		MARIO_SPRITE_RUN_2_BOTTOMRIGHT,
		MARIO_SPRITE_RUN_1_TOPLEFT,
		MARIO_SPRITE_RUN_1_TOPRIGHT,
		MARIO_SPRITE_RUN_1_BOTTOMLEFT,
		MARIO_SPRITE_RUN_1_BOTTOMRIGHT,
		MARIO_SPRITE_RUN_3_TOPLEFT,
		MARIO_SPRITE_RUN_3_TOPRIGHT,
		MARIO_SPRITE_RUN_3_BOTTOMLEFT,
		MARIO_SPRITE_RUN_3_BOTTOMRIGHT
	};
	float _yStart = 0;
};

