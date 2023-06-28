#pragma once
#include "../DynamicGameObject.h"

class Mario : public DynamicGameObject
{
public:
	Mario(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~Mario();

	void update(int frameTime, bool overrideX = false, int xOverride = 0, bool overrideY = false, int yOverride = 0) override;

	// Inherited via DynamicGameObject
	virtual void handleEvents(BitFlag* events) override;
	virtual void render() override;

protected:
};

