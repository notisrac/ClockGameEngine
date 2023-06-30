#include "TileMap.h"

TileMap::TileMap(SpriteSheet* spriteSheet, Renderer* renderer, int* tileMap, int tileMapWidth, int tileMapHeight, int viewPortWidth, int viewPortHeight) : GameObject(spriteSheet, renderer, 0, 0)
{
	_tileMap = tileMap;
	_tileMapWidth = tileMapWidth;
	_tileMapHeight = tileMapHeight;
	_viewPortWidth = viewPortWidth;
	_viewPortHeight = viewPortHeight;
}

TileMap::~TileMap()
{
}

void TileMap::handleEvents(BitFlag* events)
{
}

void TileMap::update(int frameTime)
{
}

void TileMap::render()
{
	int spriteWidth = _spriteSheet->spriteWidth();
	int spriteHeight = _spriteSheet->spriteHeight();
	int spriteId = 0;

	int xPosMod = (_xPos > (_tileMapWidth - (_viewPortWidth / spriteWidth)) * spriteWidth) ? (_tileMapWidth - (_viewPortWidth / spriteWidth)) * spriteWidth : _xPos;
	int yPosMod = (_yPos > (_tileMapHeight - (_viewPortHeight / spriteHeight)) * spriteHeight) ? (_tileMapHeight - (_viewPortHeight / spriteHeight)) * spriteHeight : _yPos;
	int startX = xPosMod / spriteWidth;
	int startY = yPosMod / spriteHeight;
	int endX = _viewPortWidth / spriteWidth + startX + 1;
	int endY = _viewPortHeight / spriteHeight + startY + 1;

	startX = (startX > _tileMapWidth - (_viewPortWidth / spriteWidth)) ? _tileMapWidth - (_viewPortWidth / spriteWidth) : startX;
	startY = (startY > _tileMapHeight - (_viewPortHeight / spriteHeight)) ? _tileMapHeight - (_viewPortHeight / spriteHeight) : startY;
	endX = (endX > _tileMapWidth) ? _tileMapWidth : endX;
	endY = (endY > _tileMapHeight) ? _tileMapHeight : endY;

	for (int i = startX; i < endX; i++)
	{
		for (int j = startY; j < endY; j++)
		{
			spriteId = _tileMap[j * _tileMapWidth + i];
			if (spriteId < 0)
			{
				continue;
			}
			_renderer->drawSprite(-1 * (xPosMod % spriteWidth) + (i - startX) * spriteWidth, -1 * (yPosMod % spriteHeight) + (j - startY) * spriteHeight, spriteWidth, spriteWidth, _spriteSheet->getSprite(spriteId));
		}
	}

}
