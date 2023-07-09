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
// TODO viewport size can be obtained from the renderer (change this in the tilemap)
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

	Renderer *renderer = new Renderer(WIDTH, HEIGHT, SCALE, "'lil Mario Clock game", 0x5cbf, 0xd97e);

	Game* game = new Game(renderer);

	// load sprite sheets
	SpriteSheet* gameSprites = new SpriteSheet(spritesheet, SPRITESHEET_WIDTH, SPRITESHEET_HEIGHT, 16, 16);
	SpriteSheet* clockFontSprites = new SpriteSheet(clock_face_font, CLOCK_FACE_FONT_DIGIT_WIDTH * 10, CLOCK_FACE_FONT_DIGIT_HEIGHT, CLOCK_FACE_FONT_DIGIT_WIDTH, CLOCK_FACE_FONT_DIGIT_HEIGHT);

	// create game objects
	//GameObject* test = new GameObject(gameSprites, renderer, 0, 0);
	//int* xx = new int[4] {0xd97e, 0xd97e, 0xd97e, 0xd97e};
	LakituCloud* lakituCloud = new LakituCloud(gameSprites, renderer, 0, 0);
	ClockFace* clockFace = new ClockFace(gameSprites, clockFontSprites, renderer, -100, 14 /*15, 14*/);
	Mario* mario = new Mario(gameSprites, renderer, 51, 78);
	TileMap* tileMap = new TileMap(gameSprites, renderer, main_tile_map, MAIN_TILEMAP_WIDTH, MAIN_TILEMAP_HEIGHT, WIDTH, HEIGHT);

	// register game objects
	game->addGameObject(tileMap);
	game->addGameObject(lakituCloud);
	game->addGameObject(clockFace);
	game->addGameObject(mario);

	// add the dynamic game objects, that represent an item on the tilemap to the tilemap
	tileMap->registerGameObject(1, clockFace);

	int cnt = 0;

	while (game->isRunning())
	{
		lastFrameTime = millis() - frameStart;
		frameStart = millis();

		//renderer->write("asdf", 10, 10);

		game->handleEvents();
		game->update(lastFrameTime);
		clockFace->update(lastFrameTime, cnt / 100, cnt % 100);
		tileMap->setPosition(mario->getXPos(), 0);
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




//
//#include <iostream>
//#include <SDL2/SDL.h>
//
////https://bitbucket.org/dandago/gigilabs/src/master/Sdl2SpriteSheets/Sdl2SpriteSheets/main.cpp
//
//// Window dimensions
//static const int WIDTH = 128;
//static const int HEIGHT = 128;
//static const int SCALE = 4;
//
//Uint32* pixels = new Uint32[WIDTH * HEIGHT];
//
//int main(int argc, char** argv)
//{
//    bool quit = false;
//    SDL_Event event;
//
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing",
//        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, 0);
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
//    //SDL_RenderSetScale(renderer, 8, 8);
//    //SDL_RenderSetLogicalSize(renderer, WIDTH * 2, HEIGHT * 2);
//
//    SDL_Texture* texture = SDL_CreateTexture(renderer,
//        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
//
//    memset(pixels, 255, WIDTH * HEIGHT * sizeof(Uint32));
//
//    pixels[(HEIGHT / 2) * WIDTH + (WIDTH / 2)] = 0;
//
//    while (!quit)
//    {
//        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(Uint32));
//
//        while (SDL_PollEvent(&event) != NULL)
//        {
//            switch (event.type)
//            {
//            case SDL_QUIT:
//                quit = true;
//                break;
//            }
//        }
//
//        SDL_RenderClear(renderer);
//        SDL_RenderCopy(renderer, texture, NULL, NULL);
//        SDL_RenderPresent(renderer);
//    }
//
//    delete[] pixels;
//    SDL_DestroyTexture(texture);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}



//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <time.h>
//
//#include <SDL2/SDL.h>
//
//// Utility macros
//#define CHECK_ERROR(test, message) \
//    do { \
//        if((test)) { \
//            fprintf(stderr, "%s\n", (message)); \
//            exit(1); \
//        } \
//    } while(0)
//
//// Get a random number from 0 to 255
//int randInt(int rmin, int rmax) {
//    return rand() % rmax + rmin;
//}
//
//// Window dimensions
//static const int width = 800;
//static const int height = 600;
//
//int main(int argc, char** argv) {
//    // Initialize the random number generator
//    srand((unsigned int)time(NULL));
//
//    // Initialize SDL
//    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
//
//    // Create an SDL window
//    SDL_Window* window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
//    CHECK_ERROR(window == NULL, SDL_GetError());
//
//    // Create a renderer (accelerated and in sync with the display refresh rate)
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    CHECK_ERROR(renderer == NULL, SDL_GetError());
//
//    // Initial renderer color
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//
//    bool running = true;
//    SDL_Event event;
//    while (running) {
//        // Process events
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//            else if (event.type == SDL_KEYDOWN) {
//                const char* key = SDL_GetKeyName(event.key.keysym.sym);
//                if (strcmp(key, "C") == 0) {
//                    SDL_SetRenderDrawColor(renderer, randInt(0, 255), randInt(0, 255), randInt(0, 255), 255);
//                }
//            }
//        }
//
//        // Clear screen
//        SDL_RenderClear(renderer);
//
//        // Draw
//        SDL_RenderDrawPoint(renderer, width / 2, height / 2);
//
//        // Show what was drawn
//        SDL_RenderPresent(renderer);
//    }
//
//    // Release resources
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
