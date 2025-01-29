#include <iostream>
#include "game.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_keycode.h"
#include "fruit.h"
#include "snake.h"
#include <deque>
#include <stdlib.h>
#include <time.h>
#include "text.h"

Game::Game()
{
	current_step_time = 0;
	last_time = 0;
	step_time = 100;

	next_move_y[0] = 1;
	next_move_x[0] = 0;

	rect = {_snake._x, _snake._y, CELL_SIZE, CELL_SIZE};
	srand(time(NULL));

	fruit_vector.emplace_back(Fruit(
		rand() % RESOLUTION * CELL_SIZE, 
		rand() % RESOLUTION * CELL_SIZE,1));

	//text->CreateText("Press Enter!");
}

void Game::Draw(SDL_Surface *surface)
{
	if ( state == PAUSED )
	{
		SDL_FillRect(surface, NULL, 0x22ffffff);
		//text->RenderText();	
	}

	for(Fruit fruit : fruit_vector)
	{
		fruit.draw(surface, &rect);
	}

	_snake.draw(&rect, surface);	
}

void Game::Update(float delta)
{
	if (state == PAUSED)
		return;

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

		_snake.move(delta);
		_snake.update(delta);
		
		if (_snake.state == _snake.DEAD)
		{
			state = PAUSED;
			Restart();
		}
		for (int i = 0; i < fruit_vector.size(); i++)
		{
			if (fruit_vector[i].x == _snake._x && fruit_vector[i].y == _snake._y)
			{
				_snake.grow(fruit_vector[i].rate);
				fruit_vector.erase(fruit_vector.begin() + i);

				fruit_vector.emplace_back(Fruit(
					rand() % RESOLUTION * CELL_SIZE, 
					rand() % RESOLUTION * CELL_SIZE,1));
			}
		}

		current_step_time = 0;
	}
}

void Game::Input(SDL_Event e)
{
	if ( state == PAUSED )
	{
		if( e.key.keysym.sym == SDLK_RETURN)
		{
			Restart();
			state = RUNNING;
		}
		return;
	}
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
		// DEBUG
		if( e.key.keysym.sym == SDLK_SPACE )
			_snake.grow(1);
	}
}

void Game::Restart()
{
	_snake.shrink(_snake._body.size() - 1);
	_snake._x = SCREEN_SIZE / 2;
	_snake._y = SCREEN_SIZE / 2;
	
	fruit_vector.clear();
	fruit_vector.emplace_back(Fruit(
		rand() % RESOLUTION * CELL_SIZE, 
		rand() % RESOLUTION * CELL_SIZE,1));
	
	_snake.revive();
}
