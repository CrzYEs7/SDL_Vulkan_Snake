#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"
#include "game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define CELL_SIZE 20

int main(int argc, char* args[])
{ 
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	
	Game game = Game();
	game.screen_width = SCREEN_WIDTH;
	game.screen_height = SCREEN_HEIGHT;
	game.cell_size = CELL_SIZE;
	game.surface = screenSurface;

	float frame_time = SDL_GetTicks();
	float last_time = SDL_GetTicks();
	float fps = 0;

	float current_step_time = 0;
	float step_time = 100;
	
	bool quit = false;
	
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 0;
	}
	
	window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if( window == NULL )
	{
		return 0;
	}
	
	screenSurface = SDL_GetWindowSurface( window );

	while( !quit )
	{
		last_time = SDL_GetTicks();

		SDL_Event e;
		while( SDL_PollEvent( &e ) )
		{ 
			if( e.type == SDL_QUIT ) quit = true; 
		//* ------------ Input ------------- *//
			game.Input(e);	
		}
		//* ------------ Update --------- *//	
		game.Update(frame_time);	
		
		// Clear Screen
		SDL_FillRect( screenSurface, NULL, 0x00000000);
	
		//* ------------ Draw ----------- *//	
		game.Draw();
		
		game._snake.draw(CELL_SIZE, game.rect, screenSurface);

		// Render
		SDL_UpdateWindowSurface( window );
		
		frame_time = SDL_GetTicks() - last_time;
		fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
		//printf("fps: %f\n", fps);
	}
	
	//Destroy window
	SDL_DestroyWindow( window );
	
	//Quit SDL subsystems
        SDL_Quit();
	
	return 0;
}
