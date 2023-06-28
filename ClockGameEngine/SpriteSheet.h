#pragma once

class SpriteSheet
{
public:
	SpriteSheet(int* spriteSheet, int width, int height, int spriteWidth, int spriteHeight);
	~SpriteSheet();

	int* getSprite(int spriteNumber);
	int spriteSize() { return _spriteWidth * _spriteHeight; }
	int spriteWidth() { return _spriteWidth; }
	int spriteHeight() { return _spriteHeight; }

private:
	int* _spriteSheet;
	int _sheetWidth;
	int _sheetHeight;
	int _spriteWidth;
	int _spriteHeight;
};