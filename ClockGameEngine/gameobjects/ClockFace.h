#pragma once
#include "../GameObject.h"

class ClockFace : public GameObject
{
public:
	ClockFace(SpriteSheet* spriteSheet, SpriteSheet* font, Renderer* renderer, int x, int y);
	~ClockFace();

	// game object update logic goes here - eg.: move game object
	void handleEvents(BitFlag* events) override;
	void update(int frameTime) override;
	void update(int frameTime, int tens, int ones);
	void render() override;
	// Inherited via GameObject

private:
	void _renderBackground(int x, int y);
	void _renderDigit(int x, int y, int digit);
	SpriteSheet* _font;
	int _digitTens = 0;
	int _digitOnes = 0;
	bool _bumpEvent = false;
};

