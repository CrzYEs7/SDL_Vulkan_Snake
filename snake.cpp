#include "snake.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_surface.h"
#include <SDL2/SDL.h>

Snake::Snake(int size, int x, int y)
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

void Snake::draw(int cell_size, SDL_Rect rect, SDL_Surface *surface)
{
	rect.x = _x;
	rect.y = _y;

	SDL_FillRect(surface, &rect, color);

	if (_body.empty())
		return;

	for (Cell cell : _body)
	{
		rect.x = cell.x;
		rect.y = cell.y;

		SDL_FillRect(surface, &rect, cell.color);
	}
}

void Snake::update()
{
	if (_body.empty())
		return;
	
	for (int i = _body.size(); i >= 1; i--)
	{
		_body[i].x = _body[i-1].x;
		_body[i].y = _body[i-1].y;
	}
	
	_body[0].x = _x;
	_body[0].y = _y;
}
