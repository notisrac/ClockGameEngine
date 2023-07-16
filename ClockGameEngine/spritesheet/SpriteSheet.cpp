#include "SpriteSheet.h"

#ifndef DESKTOP_MODE
	#include <Arduino.h>
#endif

SpriteSheet::SpriteSheet(const unsigned int* spriteSheet, int width, int height, unsigned char spriteWidth, unsigned char spriteHeight)
{
	_spriteSheet = spriteSheet;
	_sheetWidth = width;
	_sheetHeight = height;
	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;
	_pixelBuffer = new unsigned int[(unsigned int)_spriteWidth * (unsigned int)_spriteHeight] {0};
}

SpriteSheet::~SpriteSheet()
{
}

unsigned int* SpriteSheet::getSprite(unsigned char spriteNumber, bool flipped)
{
	int row = spriteNumber / (_sheetWidth / _spriteWidth);
	int col = spriteNumber % (_sheetWidth / _spriteWidth);

	for (unsigned char i = 0; i < _spriteWidth; i++)
	{
		for (unsigned char j = 0; j < _spriteHeight; j++)
		{
			_pixelBuffer[j * _spriteWidth + ((flipped) ? (_spriteWidth - 1) - i : i)] =
			#ifdef DESKTOP_MODE
				_spriteSheet[(row * _spriteHeight + j) * _sheetWidth + (col * _spriteWidth + i)];
			#else
				pgm_read_word_near(_spriteSheet + ((row * _spriteHeight + j) * _sheetWidth + (col * _spriteWidth + i)));
			#endif
		}
	}

	return _pixelBuffer;
}
