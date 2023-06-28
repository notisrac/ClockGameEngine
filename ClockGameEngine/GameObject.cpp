#include "GameObject.h"

GameObject::GameObject(SpriteSheet* spriteSheet, Renderer* renderer, int x, int y)
{
	_spriteSheet = spriteSheet;
	_renderer = renderer;
	_xPos = x;
	_yPos = y;
}

GameObject::~GameObject()
{
}

//void GameObject::update()
//{
//	// game object update logic goes here - eg.: move game object
//}
//
//void GameObject::render()
//{
//	//int* pixels = _spriteSheet->getSprite(39);
//	//_renderer->drawSprite(_xPos, _yPos, _spriteSheet->spriteWidth(), _spriteSheet->spriteWidth(), pixels);
//}
