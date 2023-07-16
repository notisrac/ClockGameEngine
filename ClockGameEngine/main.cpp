#include <windows.h>
#include <iostream>
#include <sysinfoapi.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

#include "Arduino.h"

#include "Game.h"
#include "renderer/Renderer.h"
#include "spritesheet/SpriteSheet.h"
#include "assets/gamespritesheet.h"
#include "assets/clock_face_font.h"
#include "assets/main_tilemap.h"
#include "tilemap/TileMap.h"
#include "gameobject/GameObject.h"
#include "gameobject/gameobjects/lakitucloud/LakituCloud.h"
#include "gameobject/gameobjects/clock/ClockFace.h"
#include "gameobject/gameobjects/mario/Mario.h"
#include "gameobject/gameobjects/cloud/Cloud.h"

auto startTime = high_resolution_clock().now();


// TODO add debug text print to the renderer https://thenumb.at/cpp-course/sdl2/07/07.html
// TODO get rid of the console window by setting Linker/subsystem to Windows (/SUBSYSTEM:WINDOWS)
// TODO don't try to render anything that is outside of the viewport
// TODO optimize variable size, to reduce memory footprint
// MAYBE collision detection with tilemap

// Window dimensions
#define WIDTH 128
#define HEIGHT 128
#define SCALE 4
#define FPS 60


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
	int lastClockBumpTime = 0;
	int worldXPos = 0;

	Renderer renderer = Renderer(WIDTH, HEIGHT, SCALE, "'lil Mario Clock game", 0x5cbf, 0xd97e);

	Game game = Game(&renderer);

	// load sprite sheets
	SpriteSheet gameSprites = SpriteSheet(spritesheet, SPRITESHEET_WIDTH, SPRITESHEET_HEIGHT, 16, 16);
	SpriteSheet clockFontSprites = SpriteSheet(clock_face_font, CLOCK_FACE_FONT_DIGIT_WIDTH * 10, CLOCK_FACE_FONT_DIGIT_HEIGHT, CLOCK_FACE_FONT_DIGIT_WIDTH, CLOCK_FACE_FONT_DIGIT_HEIGHT);

	// create game objects
	//GameObject* test = new GameObject(gameSprites, renderer, 0, 0);
	//int* xx = new int[4] {0xd97e, 0xd97e, 0xd97e, 0xd97e};
	//LakituCloud lakituCloud = LakituCloud(&gameSprites, &renderer, -20, -20);
	ClockFace clockFace = ClockFace(&gameSprites, &clockFontSprites, &renderer, 0, 0);
	Mario mario = Mario(&gameSprites, &renderer, 0, 80);
	TileMap tileMap = TileMap(&gameSprites, &renderer, main_tile_map, MAIN_TILEMAP_WIDTH, MAIN_TILEMAP_HEIGHT);
	Cloud cloud1 = Cloud(&gameSprites, &renderer, -20, -20, 0, 300);
	Cloud cloud2 = Cloud(&gameSprites, &renderer, -20, -20, 0, 200);

	// register game objects - this specifies the render order too!
	game.addGameObject(&tileMap);
	game.addGameObject(&cloud1);
	game.addGameObject(&cloud2);
	game.addGameObject(&clockFace);
	game.addGameObject(&mario);
	//game.addGameObject(&lakituCloud);

	// add the dynamic game objects, that represent an item on the tilemap to the tilemap
	tileMap.registerGameObject(0, &clockFace);
	tileMap.registerGameObject(1, &cloud1);
	tileMap.registerGameObject(2, &cloud2);

	int cnt = 0;
	int screenCenter = (WIDTH / 2 - mario.getWidth() / 2);

	bool automationActive = true;
	bool loopActive = true;
	unsigned long gameStart = millis();

	while (game.isRunning())
	{
		lastFrameTime = millis() - frameStart;
		frameStart = millis();

		//renderer->write("asdf", 10, 10);

		BitFlag* events = game.handleEvents();
		// render everything, including the new location for mario
		game.update(lastFrameTime);
		clockFace.update(lastFrameTime, cnt / 100, cnt % 100);

		// update the world pos ( = mario's pos)
		worldXPos = mario.getXPos();
		
		if (automationActive)
		{
			if (millis() - gameStart > 2000)
			{ // wait a few seconds on the title part of the map
				// while not in position under the clock
				if (worldXPos <= 43 * gameSprites.spriteWidth())
				{
					// keep pressing forward
					events->SetFlag(EventTypes::ButtonRight);
				}
				else
				{
					events->UnsetFlag(EventTypes::ButtonRight);
					cloud1.setSpeed(-40);
					cloud2.setSpeed(25);
				}
			}

			// break the loop on space bar
			if (events->HasFlag(EventTypes::ButtonSpace))
			{
				loopActive = false;
			}

			// loop
			if (loopActive && worldXPos >= 36 * gameSprites.spriteWidth())
			{
				worldXPos = 12 * gameSprites.spriteWidth();
				mario.setPosition(worldXPos, mario.getYPos(), false);
			}
		}



		// if mario is in the center of the screen, hold him there
		if (worldXPos > screenCenter && worldXPos < (tileMap.getWidth() - screenCenter))
		{
			mario.setPosition(screenCenter, mario.getYPos(), true);
		}
		// at the right end of the map, let mario go, so the map can stay put
		if (worldXPos >= (tileMap.getWidth() - WIDTH / 2 - mario.getWidth() / 2))
		{
			mario.setPosition(worldXPos - (tileMap.getWidth() - WIDTH), mario.getYPos(), true);
		}

		// move the tilemap based on the world pos
		if (worldXPos > screenCenter)
		{
			tileMap.setPosition(worldXPos - screenCenter, 0);
		}

		//check the collision of mario and the clock
		if (game.detectCollision(mario.getXPos(), mario.getYPos(), mario.getWidth(), mario.getHeight(), clockFace.getXPos(), clockFace.getYPos(), clockFace.getWidth(), clockFace.getHeight()))
		{
			if (millis() - lastClockBumpTime > 500)
			{
				clockFace.handleEvents(&BitFlag().SetFlag(EventTypes::ButtonReturn));
				lastClockBumpTime = millis();
				cnt++;
			}
		}

		game.render();


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

		//cnt++;
	}

	game.clean();
	renderer.close();

	return 0;
}
