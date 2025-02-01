#ifndef GAME_H
#define GAME_H

#include <deque>
#include <vector>
#include "SDL2/SDL.h"
#include "snake.h"
#include "fruit.h"
#include "text.h"

class Game
{
public:
	Game();
	~Game() = default;

public:
	Text text = Text((char*)"NovaSquare-Regular.ttf", (char*)"Press Enter to Start!", 46, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
	SDL_Rect rect;
	Snake _snake;
	std::vector<Fruit> fruit_vector;
	enum States { PAUSED, RUNNING };
	States state = PAUSED; 
	int score = 0;

public:
	void Restart();

public:
	void Update(float delta);
	void Draw(SDL_Surface *surface);
	void Input(SDL_Event e);

private:
	float last_time = SDL_GetTicks();
    
	float current_step_time;
	float step_time;
	
	std::deque<int> next_move_y;
	std::deque<int> next_move_x;

};

#endif
