#include <SDL2/SDL.h>
#include <iostream>
#include "snake.h"
#include "fruit.h"

Snake::Snake()
{
	for (int i = 0; i < _size; i++)
	{
		_body.emplace_back();
		_body.back().color = 0xffffffff;
	}
}

void Snake::draw(SDL_Rect *rect, SDL_Surface *surface)
{
	if (_body.size() < 1)
	{
		return;
	}

	for (Cell cell : _body)
	{
		rect->x = cell.x;
		rect->y = cell.y;

		SDL_FillRect(surface, rect, 0xffffffff);
	}
}

void Snake::update(float delta)
{
	if (_body.empty())
	{
		state = DEAD;
		return;
	}

	if (_x + CELL_SIZE > SCREEN_SIZE) _x = 0;
	if (_y + CELL_SIZE > SCREEN_SIZE) _y = 0;
	if (_x < 0) _x = SCREEN_SIZE - CELL_SIZE;
	if (_y < 0) _y = SCREEN_SIZE - CELL_SIZE;

	for (int i = _size - 1; i > 0; i--)
	{

		if (_body[0].x == _body[i].x && _body[0].y == _body[i].y)
		{
			//state = DEAD;
			//return;
		}

		_body[i].x = _body[i - 1].x;
		_body[i].y = _body[i - 1].y;
	}

	_body[0].x = _x;
	_body[0].y = _y;
}

void Snake::move_to(int x, int y)
{
	_x = x;
	_y = y;
}

void Snake::move(float delta)
{
	_x += direction_x * CELL_SIZE;
	_y += direction_y * CELL_SIZE;
}

const int Snake::get_speed()
{
	return _speed;
}

void Snake::set_speed(int new_speed)
{
	_speed = new_speed;
}

void Snake::grow(int n)
{
	for (int i = 0; i < n; i++)
	{
		//Cell new_cell;
		//new_cell.color = color;
		_body.emplace_back();
	}
	
	_size += n;
}

void Snake::shrink(int n)
{
	for (int i = 0; i < n; i++)
	{
		_body.pop_back();
	}
	
	_size -= n;
}

void Snake::restart()
{
	state = ALIVE;
}
