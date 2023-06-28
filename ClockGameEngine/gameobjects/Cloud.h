#pragma once
#include "../DynamicGameObject.h"

class Cloud : public DynamicGameObject
{
public:
	Cloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~Cloud();

	void update(int frameTime, bool overrideX = false, int xOverride = 0, bool overrideY = false, int yOverride = 0) override;
	void render();

	// Inherited via GameObject
	virtual void handleEvents(BitFlag* events) override;

};

