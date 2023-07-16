#ifndef CLOUD_H_
#define CLOUD_H_

#include "../../DynamicGameObject.h"

class Cloud : public DynamicGameObject
{
public:
	Cloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y, int speed, int maxDistance);
	~Cloud();

	// Inherited via DynamicGameObject
	virtual void handleEvents(BitFlag* events) override;
	virtual void update(int frameTime) override;
	virtual void render() override;
	virtual int getWidth() override
	{
		return _spriteSheet->spriteWidth() * 3;
	}
	virtual int getHeight() override
	{
		return _spriteSheet->spriteHeight() * 2;
	}
	void setSpeed(int speed)
	{
		_speed = speed;
	}

private:
	int _maxDistance = 0;
	int _speed = 0;
	float _xPosDelta = 0;
};

#endif
