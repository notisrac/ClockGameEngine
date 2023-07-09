#include "Game.h"
#include "BitFlag.h"
#include <string>

Game::Game(Renderer* renderer)
{
	_renderer = renderer;
	_isRunning = true;
}

Game::~Game()
{
}

BitFlag* Game::handleEvents()
{
	BitFlag* events = _renderer->pollEvents();

	for (unsigned char i = 0; i < _gameObjectCounter; i++)
	{
		_gameObjects[i]->handleEvents(events);
	}

	if (events->HasFlag(EventTypes::Quit))
	{
		_isRunning = false;
	}

	return events;
}

void Game::update(int frameTime)
{
	for (unsigned char i = 0; i < _gameObjectCounter; i++)
	{
		_gameObjects[i]->update(frameTime);
	}
}

void Game::render()
{
	for (unsigned char i = 0; i < _gameObjectCounter; i++)
	{
		_gameObjects[i]->render();
	}

	_renderer->renderScreen();
}

void Game::clean()
{
}

void Game::addGameObject(GameObject* object)
{
	if (_gameObjectCounter >= MAX_GAMEOBJECTS - 1)
	{
		char buf[128] = { 0 };
		sprintf_s(buf, "Cannot add new game object as maximum number of '%d' reached", MAX_GAMEOBJECTS);
		throw std::exception(buf);
	}

	_gameObjects[_gameObjectCounter] = object;
	_gameObjectCounter++;
}

bool Game::detectCollision(int aX, int aY, int aWidth, int aHeight, int bX, int bY, int bWidth, int bHeight)
{
	if (
		   aX + aWidth >= bX
		&& bX + bWidth >= aX
		&& aY + aHeight >= bY
		&& bY + bHeight >= aY
		)
	{
		return true;
	}

	return false;
}
