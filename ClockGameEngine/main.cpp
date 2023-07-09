#include <windows.h>
#include <iostream>
#include <sysinfoapi.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

#include "Renderer.h"
#include "Game.h"
#include "GameObject.h"
#include "SpriteSheet.h"
#include "resources/gamespritesheet.h"
#include "gameobjects/LakituCloud.h"
#include "resources/clock_face_font.h"
#include "gameobjects/ClockFace.h"
#include "gameobjects/Mario.h"
#include "tilemap/main_tilemap.h"
#include "tilemap/TileMap.h"

auto startTime = high_resolution_clock().now();


// TODO add debug text print to the renderer https://thenumb.at/cpp-course/sdl2/07/07.html
// TODO get rid of the console window by setting Linker/subsystem to Windows (/SUBSYSTEM:WINDOWS)
// TODO add collision detection to the game object, collision between the registered objects
// TODO don't try to render anything that is outside of the viewport
// MAYBE collision detection with tilemap

// Window dimensions
static const int WIDTH = 128;
static const int HEIGHT = 128;
static const int SCALE = 4;
static const int FPS = 60;


unsigned long millis()
{
	auto stopTime = high_resolution_clock().now();

	auto duration = duration_cast<milliseconds>(stopTime - startTime);
	return duration.count();
}

void sleep(int millis)
{
	//std::cout << millis << std::endl;
	SDL_Delay(millis);
}

int main(int argc, char** argv)
{
	const int frameDelay = 1000 / FPS;

	unsigned long frameStart = 0;
	int frameTime;
	int lastFrameTime = 0;
	int worldXPos = 0;

	Renderer *renderer = new Renderer(WIDTH, HEIGHT, SCALE, "'lil Mario Clock game", 0x5cbf, 0xd97e);

	Game* game = new Game(renderer);

	// load sprite sheets
	SpriteSheet* gameSprites = new SpriteSheet(spritesheet, SPRITESHEET_WIDTH, SPRITESHEET_HEIGHT, 16, 16);
	SpriteSheet* clockFontSprites = new SpriteSheet(clock_face_font, CLOCK_FACE_FONT_DIGIT_WIDTH * 10, CLOCK_FACE_FONT_DIGIT_HEIGHT, CLOCK_FACE_FONT_DIGIT_WIDTH, CLOCK_FACE_FONT_DIGIT_HEIGHT);

	// create game objects
	//GameObject* test = new GameObject(gameSprites, renderer, 0, 0);
	//int* xx = new int[4] {0xd97e, 0xd97e, 0xd97e, 0xd97e};
	LakituCloud* lakituCloud = new LakituCloud(gameSprites, renderer, 0, 0);
	ClockFace* clockFace = new ClockFace(gameSprites, clockFontSprites, renderer, 0, 0);
	Mario* mario = new Mario(gameSprites, renderer, 5, 80);
	TileMap* tileMap = new TileMap(gameSprites, renderer, main_tile_map, MAIN_TILEMAP_WIDTH, MAIN_TILEMAP_HEIGHT);

	// register game objects
	game->addGameObject(tileMap);
	game->addGameObject(lakituCloud);
	game->addGameObject(clockFace);
	game->addGameObject(mario);

	// add the dynamic game objects, that represent an item on the tilemap to the tilemap
	tileMap->registerGameObject(1, clockFace);

	int cnt = 0;
	int screenCenter = (WIDTH / 2 - mario->getWidth() / 2);

	while (game->isRunning())
	{
		lastFrameTime = millis() - frameStart;
		frameStart = millis();

		//renderer->write("asdf", 10, 10);

		game->handleEvents();
		// render everything, including the new location for mario
		game->update(lastFrameTime);
		clockFace->update(lastFrameTime, cnt / 100, cnt % 100);
		// update the world pos ( = mario's pos)
		worldXPos = mario->getXPos();
		// if mario is in the center of the screen, hold him there
		if (worldXPos > screenCenter && worldXPos < (tileMap->getWidth() - screenCenter))
		{
			mario->setPosition(screenCenter, mario->getYPos());
		}
		// at the right end of the map, let mario go, so the map can stay put
		if (worldXPos >= (tileMap->getWidth() - WIDTH / 2 - mario->getWidth() / 2))
		{
			mario->setPosition(worldXPos - (tileMap->getWidth() - WIDTH), mario->getYPos());
		}

		// move the tilemap based on the world pos
		if (worldXPos > screenCenter)
		{
			tileMap->setPosition(worldXPos - screenCenter, 0);
		}

		if (game->detectCollision(mario->getXPos(), mario->getYPos(), mario->getWidth(), mario->getHeight(), clockFace->getXPos(), clockFace->getYPos(), clockFace->getWidth(), clockFace->getHeight()))
		{
			std::cout << "collision" << std::endl;
		}

		game->render();


		//test->render();
		//renderer->setPixel(0, 0, 0xd97e);
		//renderer->setPixel(1, 1, 0xd97e);
		//renderer->drawSprite(0, 0, 2, 2, xx);

		// time took to process and render frame, in ms
		frameTime = millis() - frameStart;

		if (frameDelay > frameTime)
		{
			sleep(frameDelay - frameTime);
		}

		cnt++;
	}

	game->clean();
	renderer->close();

	return 0;
}
