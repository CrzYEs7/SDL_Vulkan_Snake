#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_stdinc.h"
#include "cell.h"
#include "globals.h"

class Snake
{
public:
	Snake(int size = 1, int x = 0, int  = 0);
	int _y = 0;
	int _x = 0;
	int direction_x = 0;
	int direction_y = 0;
	int _speed = 1;
	Uint32 color = 0xffffffff;

public:
	void move_to(int x, int y);
	void move(float delta);
	int get_speed();
	void set_speed(int new_speed);
	int get_size();
	void grow(int n);
	void draw(SDL_Rect *rect, SDL_Surface *Surface);
	void update(float delta);
	std::vector<Cell> _body;

private:
	int _size = 1;
};

#endif
