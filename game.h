#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "snake.h"
#include <deque>

class Game
{
public:
	Game();
	~Game() = default;
public:
	void Update(float delta);
	void Draw(SDL_Surface *surface);
	void Input(SDL_Event e);

public:
	int screen_width;
	int screen_height;
	int cell_size;
	
	SDL_Rect rect;
	Snake _snake;
private:
	float last_time = SDL_GetTicks();

	float current_step_time;
	float step_time;
	
	std::deque<int> next_move_y;
	std::deque<int> next_move_x;
};

#endif
