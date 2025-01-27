#include <iostream>
#include <stdio.h>
#include "game.h"
#include "SDL2/SDL.h"
#include "snake.h"
#include <deque>
#include <ostream>

Game::Game()
{
	current_step_time = 0;
	last_time = 0;
	step_time = 100;
	cell_size = 20;

	next_move_y[0] = 1;
	next_move_x[0] = 0;

	_snake = {0, 0, 0};
	_snake._speed = 800 / cell_size;

	rect = {_snake._x, _snake._y, screen_width / cell_size, screen_height / cell_size};
}

void Game::Draw()
{
	_snake.draw(cell_size, rect, surface);	
}

void Game::Update(float delta)
{
	current_step_time += delta;

	if (current_step_time >= step_time)
	{
		if (next_move_y.size() > 0)
		{	
			_snake.direction_y = next_move_y.front();
			_snake.direction_x = next_move_x.front();
			next_move_x.pop_front();
			next_move_y.pop_front();
		}
		printf("snake dir_x: %i, dir_y: %i\n", _snake.direction_x , _snake.direction_y);
		_snake.update();
		_snake.move(_snake.direction_x,_snake.direction_y , delta);
		current_step_time = 0;
	}

	if (_snake._x + screen_width / cell_size > screen_width ) _snake._x = 0;
	if (_snake._y + screen_height / cell_size > screen_height) _snake._y = 0;
	if (_snake._x < 0) _snake._x = screen_width - screen_width / cell_size;
	if (_snake._y < 0) _snake._y = screen_height - screen_height / cell_size;

	std::cout << "snake x" << _snake._x << "snake y" << _snake._y << std::endl;
}

void Game::Input(SDL_Event e)
{
	if (e.key.type == SDL_KEYDOWN)
	{
		if( e.key.keysym.sym == SDLK_UP )
		{
			next_move_y.emplace_back(-1);
			next_move_x.emplace_back(0);
		}
		if( e.key.keysym.sym == SDLK_DOWN )
		{
			next_move_y.emplace_back(1);
			next_move_x.emplace_back(0);
		}
		if( e.key.keysym.sym == SDLK_LEFT )
		{
			next_move_y.emplace_back(0);
			next_move_x.emplace_back(-1);
		}
		if( e.key.keysym.sym == SDLK_RIGHT )
		{
			next_move_y.emplace_back(0);
			next_move_x.emplace_back(1);
		}
	}
}
