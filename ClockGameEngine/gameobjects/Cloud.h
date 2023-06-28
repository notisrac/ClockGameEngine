#pragma once
#include "../DynamicGameObject.h"

class Cloud : public DynamicGameObject
{
public:
	Cloud(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y);
	~Cloud();

	// Inherited via DynamicGameObject
	void handleEvents(BitFlag* events) override;
	void update(int frameTime) override;
	void render() override;

};

