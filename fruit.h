#ifndef FRUIT_H
#define FRUIT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_surface.h"
#include "globals.h"

class Fruit
{
public:
    enum feature {timer};

public:
	Fruit(int _x, int _y, int _rate);
	~Fruit() = default;

public:
	void draw(SDL_Surface *surface, SDL_Rect *rect);
    
public:
    bool hasFeature(feature f);

public:
	int x;
	int y;
	int rate;
	Uint32 color;
    float lifespam = 0;
    std::vector<int> features;

};

#endif

