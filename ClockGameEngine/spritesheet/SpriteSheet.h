#pragma once

class SpriteSheet
{
public:
	SpriteSheet(const unsigned int* spriteSheet, int width, int height, unsigned char spriteWidth, unsigned char spriteHeight);
	~SpriteSheet();

	unsigned int* getSprite(unsigned char spriteNumber, bool flipped = false);
	unsigned int spriteSize() { return _spriteWidth * _spriteHeight; }
	unsigned char spriteWidth() { return _spriteWidth; }
	unsigned char spriteHeight() { return _spriteHeight; }

private:
	const unsigned int* _spriteSheet;
	int _sheetWidth;
	int _sheetHeight;
	unsigned char _spriteWidth;
	unsigned char _spriteHeight;
};