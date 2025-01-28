#include <stdio.h>
#include <SDL2/SDL.h>
#include "globals.h"
#include "game.h"

int main(int argc, char* args[])
{ 
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
		return 0;

	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN);
	if( window == NULL )
		return 0;

	SDL_Surface* screenSurface = SDL_GetWindowSurface( window );

	Game game;

	float frame_time = SDL_GetTicks();
	float last_time = SDL_GetTicks();
	float fps = 0;

	bool quit = false;

	while( !quit )
	{

		SDL_Event e;
		while( SDL_PollEvent( &e ) )
		{ 
			if( e.type == SDL_QUIT )
				quit = true;

		//* ------------ Input ------------- *//
			game.Input(e);	
		}
		
		last_time = SDL_GetTicks();

		//* ------------ Update --------- *//	
		game.Update(frame_time);	
		
		// Clear Screen
		SDL_FillRect( screenSurface, NULL, 0x00000000);

		//* ------------ Draw ----------- *//	
		game.Draw(screenSurface);
		
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
