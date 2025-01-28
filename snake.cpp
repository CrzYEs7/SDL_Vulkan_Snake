#include <SDL2/SDL.h>
#include <iostream>
#include "snake.h"

Snake::Snake(int size, int x, int y)
{
	_size = size;
	_x = x;
	_y = y;
	_speed = 1;

	for (int i = 0; i < _size; i++)
	{
		Cell new_cell;
		new_cell.color = color;
		_body.emplace_back(new_cell);
	}
}

void Snake::draw(SDL_Rect *rect, SDL_Surface *surface)
{
	if (_body.size() < 1)
	{
		std::cout << "dead front snake::draw" << std::endl;
		return;
	}
	for (Cell cell : _body)
	{
		rect->x = cell.x;
		rect->y = cell.y;

		SDL_FillRect(surface, rect, cell.color);
	}
}

void Snake::update(float delta)
{
	if (_body.empty())
		return;
	
	if (_x + CELL_SIZE > SCREEN_SIZE ) _x = 0;
	if (_y + CELL_SIZE > SCREEN_SIZE) _y = 0;
	if (_x < 0) _x = SCREEN_SIZE - CELL_SIZE;
	if (_y < 0) _y = SCREEN_SIZE - CELL_SIZE;

	for (int i = _body.size() - 1; i >= 1; i--)
	{
		_body[i].x = _body[i-1].x;
		_body[i].y = _body[i-1].y;
		std::cout << "cell :" << i << " x: " << _body[i].x << " y: " << _body[i].y << std::endl;
	}

	_body[0].x = _x;
	_body[0].y = _y;

	std::cout << "cell : " << 0 << " x: " << _body[0].x << " y: " << _body[0].y << std::endl;
}

void Snake::move_to(int x, int y)
{
	_x = x;
	_y = y;
}

void Snake::move(float delta)
{
	_x += direction_x * _speed;
	_y += direction_y * _speed;
}

int Snake::get_size()
{
	return _size;
}

int Snake::get_speed()
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
		Cell new_cell;
		new_cell.color = color;
		_body.emplace_back(new_cell);
	}
	
	_size += n;
}


