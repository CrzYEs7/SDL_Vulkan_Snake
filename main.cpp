#include <stdio.h>
#include <SDL2/SDL.h>
#include "snake.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CELL_SIZE 20

int main(int argc, char* args[])
{ 
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	float frame_time = SDL_GetTicks();
	float last_time = SDL_GetTicks();
	float fps = 0;

	float current_step_time = 0;
	float step_time = 100;
	
	SDL_Event e;
	bool quit = false;

	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 0;
	}

	float sdl_start_time = SDL_GetTicks();
	
	window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if( window == NULL )
	{
		return 0;
	}
	
	screenSurface = SDL_GetWindowSurface( window );
	
	
	Snake snake{1, 10, 10};
	snake._speed = 20;

	SDL_Rect rect = {snake._x, snake._y, CELL_SIZE, CELL_SIZE};
	
	SDL_FillRect( screenSurface, &rect, 0xffffffff); 
	SDL_UpdateWindowSurface( window );

	while( !quit )
	{
		while( SDL_PollEvent( &e ) )
		{ 
			if( e.type == SDL_QUIT ) quit = true; 

			if( e.key.keysym.sym == SDLK_UP )
			{
				snake.direction_y = -1;
				snake.direction_x = 0;
			}
			if( e.key.keysym.sym == SDLK_DOWN )
			{
				snake.direction_y = 1;
				snake.direction_x = 0;
			}
			if( e.key.keysym.sym == SDLK_LEFT )
			{
				snake.direction_x = -1;
				snake.direction_y = 0;
			}
			if( e.key.keysym.sym == SDLK_RIGHT )
			{
				snake.direction_x = 1;
				snake.direction_y = 0;
			}
		}

		last_time = SDL_GetTicks();
		
		current_step_time += frame_time;

		if (current_step_time >= step_time)
		{
			snake.move(snake.direction_x,snake.direction_y , frame_time);
			rect.x = snake._x;
			rect.y = snake._y;
			current_step_time = 0;
		}

		SDL_FillRect( screenSurface, NULL, 0x00000000);
		SDL_FillRect( screenSurface, &rect, 0xffffffff);

		SDL_UpdateWindowSurface( window );

		if (snake._x > SCREEN_WIDTH ) snake._x = 0;
		if (snake._y > SCREEN_HEIGHT) snake._y = 0;
		if (snake._x < 0) snake._x = SCREEN_WIDTH;
		if (snake._y < 0) snake._y = SCREEN_HEIGHT;

			 
		
		frame_time = SDL_GetTicks() - last_time;
		fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
		printf("fps: %f\n", fps);
	}
	
	//Destroy window
	SDL_DestroyWindow( window );
	
	//Quit SDL subsystems
        SDL_Quit();
	
	return 0;
}
