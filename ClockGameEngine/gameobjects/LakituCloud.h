#pragma once
#include "../DynamicGameObject.h"

class LakituCloud : public DynamicGameObject
{
public:
	LakituCloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~LakituCloud();

	// Inherited via DynamicGameObject
	void handleEvents(BitFlag* events) override;
	void update(int frameTime) override;
	void render() override;

};

