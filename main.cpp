#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL not initialized! SDL_Error:%n\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( window == NULL )
	        {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return -1;
		
		}
		
		screenSurface = SDL_GetWindowSurface( window );
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

		SDL_UpdateWindowSurface( window );

		SDL_Event e;
		bool quit = false;
		while( quit == false )
		{ 
			while( SDL_PollEvent( &e ) )
			{ 
				if( e.type == SDL_QUIT ) quit = true; 
			} 
		}

	}
	
	//Destroy window
	SDL_DestroyWindow( window );
	
	//Quit SDL subsystems
        SDL_Quit();
	
	return 0;


}
