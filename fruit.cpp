#include "fruit.h"

Fruit::Fruit(int _x, int _y, int _rate)
{
	x = _x;
	y = _y;
	rate = _rate;
	color = 0xffff0000;
}
void Fruit::draw(SDL_Surface *surface, SDL_Rect *rect)
{
	rect->x = x;
	rect->y = y;
	SDL_FillRect(surface, rect, color);
}
