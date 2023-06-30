#pragma once
#include "GameObject.h"

class TileMap : public GameObject
{
public:
	TileMap(SpriteSheet* spriteSheet, Renderer* renderer, int* tileMap, int tileMapWidth, int tileMapHeight, int viewPortWidth, int viewPortHeight);
	~TileMap();

	// Inherited via GameObject
	virtual void handleEvents(BitFlag* events) override;
	virtual void update(int frameTime) override;
	virtual void render() override;

private:
	int* _tileMap;
	int _viewPortWidth = 0;
	int _viewPortHeight = 0;
	int _tileMapWidth = 0;
	int _tileMapHeight = 0;
};

