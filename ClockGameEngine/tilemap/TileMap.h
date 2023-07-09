#pragma once
#include "../GameObject.h"
#include "../Dictionary.h"
#include "../DynamicGameObject.h"

#define TILEMAP_OBJECTS_ID_START 200
#define TILEMAP_EMPTY_TILE_ID 255

class TileMap : public GameObject
{
public:
	TileMap(SpriteSheet* spriteSheet, Renderer* renderer, int* tileMap, int tileMapWidth, int tileMapHeight);
	~TileMap();

	void registerGameObject(unsigned char id, DynamicGameObject* object);

	// Inherited via GameObject
	virtual void handleEvents(BitFlag* events) override;
	virtual void update(int frameTime) override;
	virtual void render() override;
	virtual int getWidth() override
	{
		return _spriteSheet->spriteWidth() * _tileMapWidth;
	}
	virtual int getHeight() override
	{
		return _spriteSheet->spriteHeight() * _tileMapHeight;
	}

private:
	int* _tileMap;
	int _tileMapWidth = 0;
	int _tileMapHeight = 0;
	Dictionary<DynamicGameObject, 1> _gameObjects;
};

