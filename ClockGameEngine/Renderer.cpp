#include "Renderer.h"
#include <SDL2/SDL.h>
#include "BitFlag.h"

#include <SDl2/SDL_ttf.h>
#include <stdexcept>

Renderer::Renderer(int width, int height, int scale, const char* windowTitle, unsigned short backgroundColor, unsigned short transparentColor)
{
    _width = width;
    _height = height;
    _scale = scale;
    _backgroundColor = backgroundColor;
    _transparentColor = transparentColor;

    //_pixels = new Uint32[_width * _height];
    _pixels = new unsigned short[_width * _height];

    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow(windowTitle,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width * _scale, _height * _scale, 0);

    _renderer = SDL_CreateRenderer(_window, -1, 0);

    _texture = SDL_CreateTexture(_renderer,
        SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, _width, _height);

    memset(_pixels, _backgroundColor, _width * _height * sizeof(unsigned short));

    TTF_Init();
    _font = TTF_OpenFont("resources/LucidaSansRegular.ttf", 14);
    if (!_font)
    {
        throw std::exception("Could not load font!");
    }

    // set up the overlay texture
    //_overlayTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _width, _height);
    //SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);

    _overlayColor = SDL_Color();
    _overlayColor.r = 255;
    _overlayColor.g = 0;
    _overlayColor.b = 255;
}

Renderer::~Renderer()
{
}

void Renderer::setPixel(int x, int y, int color)
{
    if (x >= _width || y >= _height || x < 0 || y < 0)
    {
        return;
    }

    if (color == _transparentColor)
    { // transparent color
        return;
    }
    _pixels[y * _width + x] = color;

}

void Renderer::drawSprite(int x, int y, int width, int height, int* pixels)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            setPixel(x + i, y + j, pixels[j * width + i]);
        }
    }
    // free up the memory space allocated for the sprite
    delete pixels;
}

void Renderer::renderScreen()
{
    SDL_UpdateTexture(_texture, NULL, _pixels, _width * sizeof(unsigned short));

    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, NULL, NULL);

    // TODO fix this
    //SDL_Rect position = SDL_Rect();
    //position.x = 1;
    //position.y = 1;
    //SDL_QueryTexture(_overlayTexture, nullptr, nullptr, &position.w, &position.h);
    //SDL_RenderCopy(_renderer, _overlayTexture, NULL, &position);

    SDL_RenderPresent(_renderer);
    fillBackground(_backgroundColor);
}

void Renderer::fillBackground(unsigned short color)
{
    for (int i = 0; i < _width * _height; i++)
    {
        _pixels[i] = color;
    }
}

BitFlag* Renderer::pollEvents()
{
    while (SDL_PollEvent(&_event) != NULL)
    {
        switch (_event.type)
        {
            case SDL_QUIT:
                _eventsBitFlag.SetFlag(EventTypes::Quit);
                break;
            case SDL_KEYDOWN:
                switch (_event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    _eventsBitFlag.SetFlag(EventTypes::ButtonLeft);
                    break;
                case SDLK_RIGHT:
                    _eventsBitFlag.SetFlag(EventTypes::ButtonRight);
                    break;
                case SDLK_UP:
                    _eventsBitFlag.SetFlag(EventTypes::ButtonUp);
                    break;
                case SDLK_DOWN:
                    _eventsBitFlag.SetFlag(EventTypes::ButtonDown);
                    break;
                case SDLK_RETURN:
                    _eventsBitFlag.SetFlag(EventTypes::ButtonReturn);
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (_event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    _eventsBitFlag.UnsetFlag(EventTypes::ButtonLeft);
                    break;
                case SDLK_RIGHT:
                    _eventsBitFlag.UnsetFlag(EventTypes::ButtonRight);
                    break;
                case SDLK_UP:
                    _eventsBitFlag.UnsetFlag(EventTypes::ButtonUp);
                    break;
                case SDLK_DOWN:
                    _eventsBitFlag.UnsetFlag(EventTypes::ButtonDown);
                    break;
                case SDLK_RETURN:
                    _eventsBitFlag.UnsetFlag(EventTypes::ButtonReturn);
                    break;
                }
                break;
        }
    }

    return &_eventsBitFlag;
}

void Renderer::debugWrite(const char* text)
{
    // TODO fix this
    SDL_Surface* surf = TTF_RenderText_Blended(_font, text, _overlayColor);
    _overlayTexture = SDL_CreateTextureFromSurface(_renderer, surf);
    SDL_FreeSurface(surf);
}

void Renderer::close()
{
    SDL_DestroyTexture(_texture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
