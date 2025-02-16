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
	Snake();
	int _y = 0;
	int _x = 0;
	int direction_x = 0;
	int direction_y = 0;
	int _speed = 1;
	Uint32 color = 0xffffffff;
	std::vector<Cell> _body;
	
	enum States { DEAD, ALIVE, IMORTAL };
	States state = ALIVE;


public:
	void set_speed(int new_speed);
	void move_to(int x, int y);
	void move(float delta);
	void grow(int n);
	void shrink(int n);
	void restart();
	int get_speed();

public:
	void draw(SDL_Rect* rect, SDL_Surface *Surface);
	void update(float delta);

private:
	int _size = 1;
};

#endif
