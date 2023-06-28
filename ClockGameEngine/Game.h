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

	bool isRunning() {
		return _isRunning;
	}

private:
	bool _isRunning = false;
	Renderer* _renderer = nullptr;
	GameObject* _gameObjects[MAX_GAMEOBJECTS] = { NULL };
	unsigned char _gameObjectCounter = 0;
};

