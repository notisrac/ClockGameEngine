#pragma once
#include "../DynamicGameObject.h"

class Mario : public DynamicGameObject
{
public:
	Mario(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~Mario();

	// Inherited via DynamicGameObject
	virtual void handleEvents(BitFlag* events) override;
	virtual void update(int frameTime) override;
	virtual void render() override;

protected:
};

