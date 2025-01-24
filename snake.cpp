#include "snake.h"

Snake::Snake(int size = 1, int x = 0, int y = 0)
{
	_size = size;
	_x = x;
	_y = y;
	_speed = 1;
}

void Snake::move_to(int x, int y)
{
	_x = x;
	_y = y;
}

void Snake::move(int x, int y, float delta)
{
	_x += x * _speed * delta;
	_y += y * _speed * delta;
}

int Snake::get_speed()
{
	return _speed;
}

void Snake::set_speed(int new_speed)
{
	_speed = new_speed;
}

int Snake::get_size()
{
	return _size;
}

void Snake::set_sizes(int new_size)
{
	_size = new_size;
}
