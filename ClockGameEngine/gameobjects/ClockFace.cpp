#include "ClockFace.h"

ClockFace::ClockFace(SpriteSheet* spriteSheet, SpriteSheet* font, Renderer* renderer, int x, int y) : GameObject(spriteSheet, renderer, x, y)
{
	_font = font;
}

ClockFace::~ClockFace()
{
}

void ClockFace::update(int frameTime, int tens, int ones)
{
	GameObject::update(frameTime);
	_digitTens = tens;
	_digitOnes = ones;
}

void ClockFace::_renderBackground(int x, int y)
{
	const int spriteWidth = _spriteSheet->spriteWidth();
	const int spriteHeight = _spriteSheet->spriteHeight();
	// left bg top row
	_renderer->drawSprite(x                  , y                   , spriteWidth, spriteHeight, _spriteSheet->getSprite(14));
	_renderer->drawSprite(x + spriteWidth    , y                   , spriteWidth, spriteHeight, _spriteSheet->getSprite(15));
	_renderer->drawSprite(x + 2 * spriteWidth, y                   , spriteWidth, spriteHeight, _spriteSheet->getSprite(16));
	// left bg middle row 
	_renderer->drawSprite(x                  , y + spriteHeight    , spriteWidth, spriteHeight, _spriteSheet->getSprite(17));
	_renderer->drawSprite(x + spriteWidth    , y + spriteHeight    , spriteWidth, spriteHeight, _spriteSheet->getSprite(18));
	_renderer->drawSprite(x + 2 * spriteWidth, y + spriteHeight    , spriteWidth, spriteHeight, _spriteSheet->getSprite(19));
	// left bg bottom row 
	_renderer->drawSprite(x                  , y + 2 * spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(20));
	_renderer->drawSprite(x + spriteWidth    , y + 2 * spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(21));
	_renderer->drawSprite(x + 2 * spriteWidth, y + 2 * spriteHeight, spriteWidth, spriteHeight, _spriteSheet->getSprite(22));
}

void ClockFace::_renderDigit(int x, int y, int digit)
{
	_renderer->drawSprite(x, y, _font->spriteWidth(), _font->spriteHeight(), _font->getSprite(digit));
}

void ClockFace::handleEvents(BitFlag* events)
{
}

void ClockFace::render()
{
	// tens
	_renderBackground(_xPos, _yPos);
	_renderDigit(_xPos + 5, _yPos + 12, _digitTens / 10);
	_renderDigit(_xPos + 25, _yPos + 12, _digitTens % 10);

	// ones
	_renderBackground(_xPos + 3 * _spriteSheet->spriteWidth(), _yPos);
	_renderDigit(_xPos + 48 + 5, _yPos + 12, _digitOnes / 10);
	_renderDigit(_xPos + 48 + 25, _yPos + 12, _digitOnes % 10);
}
