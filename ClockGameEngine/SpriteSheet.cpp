#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(int* spriteSheet, int width, int height, int spriteWidth, int spriteHeight)
{
	_spriteSheet = spriteSheet;
	_sheetWidth = width;
	_sheetHeight = height;
	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;
}

SpriteSheet::~SpriteSheet()
{
}

int* SpriteSheet::getSprite(int spriteNumber)
{
	int* a = new int[_spriteWidth * _spriteHeight]{0};

	int row = spriteNumber / (_sheetWidth / _spriteWidth);
	int col = spriteNumber % (_sheetWidth / _spriteWidth);

	int startPos = (row * _spriteHeight) * _sheetWidth + (col * _spriteWidth);

	for (int i = 0; i < _spriteWidth; i++)
	{
		for (int j = 0; j < _spriteHeight; j++)
		{
			a[j * _spriteWidth + i] = _spriteSheet[(row * _spriteHeight + j) * _sheetWidth + (col * _spriteWidth + i)];
		}
	}

	return a;
}
