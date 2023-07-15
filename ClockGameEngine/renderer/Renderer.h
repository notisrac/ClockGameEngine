#pragma once
#include <SDL2/SDL.h>
#include "../BitFlag.h"
#include <SDL2/SDL_ttf.h>

class Renderer
{
public:
	Renderer(int width, int height, int scale, const char* windowTitle, unsigned short backgroundColor, unsigned short transparentColor);
	~Renderer();

	void setPixel(int x, int y, int color);
	void drawSprite(int x, int y, int width, int height, unsigned int* pixels);
	void renderScreen();
	void fillBackground(unsigned short color);
	BitFlag* pollEvents();
	const int getWidth() const { return _width;	}
	const int getHeight() const { return _height; }
	void debugWrite(const char* text);

	void close();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Event _event;
	int _width;
	int _height;
	int _scale;
	//Uint32* _pixels;
	unsigned short* _pixels;
	TTF_Font* _font;
	SDL_Texture* _overlayTexture;
	SDL_Color _overlayColor;
	unsigned short _backgroundColor;
	unsigned short _transparentColor;
	BitFlag _eventsBitFlag;
};

