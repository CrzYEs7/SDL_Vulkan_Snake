#include "snake.h"

void Snake::Snake(Uint32 size, int x = 0, int y = 0)
{
	_size = size;
	_x = _x;
	_y = _y;
	_speed = 1;
}

void move_to(int x, int y)
{
	_x = x;
	_y = y;
}

int get_speed(){
{
	return _speed;
}

int set_speed(float new_speed){
{
	_speed = new_speed;
}

Uint32 get_size()
{
	return _size;
}

Uint32 set_sizes(Uint32 new_size)
{
	_size = new_size;
}

float _speed = 1;
Uint32 _size = size;
