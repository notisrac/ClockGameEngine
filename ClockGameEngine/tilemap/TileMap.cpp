#include "TileMap.h"

TileMap::TileMap(SpriteSheet* spriteSheet, Renderer* renderer, const unsigned char* tileMap, int tileMapWidth, int tileMapHeight) : GameObject(spriteSheet, renderer, 0, 0)
{
	_tileMap = tileMap;
	_tileMapWidth = tileMapWidth;
	_tileMapHeight = tileMapHeight;
}

TileMap::~TileMap()
{
}

void TileMap::registerGameObject(unsigned char id, DynamicGameObject* object)
{
	_gameObjects.add(id, object);
}

void TileMap::handleEvents(BitFlag* events)
{
}

void TileMap::update(int frameTime)
{
	// find all of the game objects on the tilemap and update their position relative to it
	//for (unsigned char i = 0; i < _gameObjects.count(); i++)
	//{
	//}

	// for (int i = 0; i < _tileMapWidth * _tileMapHeight; i++)
	// {

	// }
}

void TileMap::render()
{
	int viewPortWidth = _renderer->getWidth();
	int viewPortHeight = _renderer->getHeight();
	int spriteWidth = _spriteSheet->spriteWidth();
	int spriteHeight = _spriteSheet->spriteHeight();
	unsigned char spriteId = 0;

	int xPosMod = (_xPos > (_tileMapWidth - (viewPortWidth / spriteWidth)) * spriteWidth) ? (_tileMapWidth - (viewPortWidth / spriteWidth)) * spriteWidth : _xPos;
	int yPosMod = (_yPos > (_tileMapHeight - (viewPortHeight / spriteHeight)) * spriteHeight) ? (_tileMapHeight - (viewPortHeight / spriteHeight)) * spriteHeight : _yPos;
	int startX = xPosMod / spriteWidth;
	int startY = yPosMod / spriteHeight;
	int endX = viewPortWidth / spriteWidth + startX + 1;
	int endY = viewPortHeight / spriteHeight + startY + 1;

	startX = (startX > _tileMapWidth - (viewPortWidth / spriteWidth)) ? _tileMapWidth - (viewPortWidth / spriteWidth) : startX;
	startY = (startY > _tileMapHeight - (viewPortHeight / spriteHeight)) ? _tileMapHeight - (viewPortHeight / spriteHeight) : startY;
	endX = (endX > _tileMapWidth) ? _tileMapWidth : endX;
	endY = (endY > _tileMapHeight) ? _tileMapHeight : endY;

	for (int i = 0; i < _tileMapWidth; i++)
	{
		for (int j = 0; j < _tileMapHeight; j++)
		{
			spriteId =
			#ifdef DESKTOP_MODE
				_tileMap[j * _tileMapWidth + i];
			#else
				pgm_read_byte_near(_tileMap + (j * _tileMapWidth + i));
			#endif
			if (spriteId == TILEMAP_EMPTY_TILE_ID)
			{ // empty tile
				continue;
			}

			if (spriteId >= TILEMAP_OBJECTS_ID_START)
			{ // registered game object - just need to update the position
				_gameObjects[spriteId - TILEMAP_OBJECTS_ID_START].object->setPosition(-1 * (xPosMod % spriteWidth) + (i - startX) * spriteWidth, -1 * (yPosMod % spriteHeight) + (j - startY) * spriteHeight, false);
				continue;
			}

			if (i < startX || i > endX || j < startY || j > endY)
			{ // don't render anything outside the viewport
				continue;
			}

			// render the actual tile
			_renderer->drawSprite(-1 * (xPosMod % spriteWidth) + (i - startX) * spriteWidth, -1 * (yPosMod % spriteHeight) + (j - startY) * spriteHeight, spriteWidth, spriteWidth, _spriteSheet->getSprite(spriteId));
		}
	}
}
