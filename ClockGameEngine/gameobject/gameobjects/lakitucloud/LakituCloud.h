#ifndef LAKITUCLOUD_H_
#define LAKITUCLOUD_H_

#include "../../DynamicGameObject.h"

class LakituCloud : public DynamicGameObject
{
public:
	LakituCloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~LakituCloud();

	// Inherited via DynamicGameObject
	void handleEvents(BitFlag* events) override;
	void update(int frameTime) override;
	void render() override;
	virtual int getWidth() override
	{
		return _spriteSheet->spriteWidth() * 1;
	}
	virtual int getHeight() override
	{
		return _spriteSheet->spriteHeight() * 1;
	}

};

#endif
