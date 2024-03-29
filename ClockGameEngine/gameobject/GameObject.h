#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <stdexcept>

#include "../renderer/Renderer.h"
#include "../spritesheet/SpriteSheet.h"

class GameObject
{
public:
	GameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y)
	{
		_spriteSheet = spriteSheet;
		_renderer = renderer;
		_xPos = x;
		_yPos = y;
	}
	~GameObject()
	{
	}

	virtual void handleEvents(BitFlag* events) = 0;
	// game object update logic goes here - eg.: move game object
	virtual void update(int frameTime) = 0;
	virtual void render() = 0;
	virtual void setPosition(int x, int y)
	{
		_posOverwrite = true;
		_xPos = x;
		_yPos = y;
	}
	virtual int getXPos()
	{
		return _xPos;
	}
	virtual int getYPos()
	{
		return _yPos;
	}
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

protected:
	SpriteSheet* _spriteSheet;
	Renderer* _renderer;
	int _xPos = 0;
	int _yPos = 0;
	bool _posOverwrite = false;
};

#endif