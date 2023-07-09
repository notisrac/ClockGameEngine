#pragma once
#include "Renderer.h"
#include "GameObject.h"

#define MAX_GAMEOBJECTS 32

class Game
{
public:
	Game(Renderer* renderer);
	~Game();

	BitFlag* handleEvents();
	void update(int frameTime);
	void render();
	void clean();

	void addGameObject(GameObject* object);
	unsigned char gameObjectCount()
	{
		return _gameObjectCounter;
	}

	bool isRunning() {
		return _isRunning;
	}

	bool detectCollision(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight);

private:
	bool _isRunning = false;
	Renderer* _renderer = nullptr;
	GameObject* _gameObjects[MAX_GAMEOBJECTS] = { nullptr };
	unsigned char _gameObjectCounter = 0;
};

