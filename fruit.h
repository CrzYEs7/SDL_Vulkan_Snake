#ifndef FRUIT_H
#define FRUIT_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_surface.h"
#include "globals.h"

class Fruit
{
public:
	Fruit(int x, int y);
	~Fruit() = default;
public:
	void draw(SDL_Surface *surface, SDL_Rect *rect);

public:
	int x;
	int y;
	int rate;
	Uint32 color;
};

#endif

