#include "Game.h"
#include "BitFlag.h"

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
	_gameObjects[_gameObjectCounter] = object;
	_gameObjectCounter++;
}
