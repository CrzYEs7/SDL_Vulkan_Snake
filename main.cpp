#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	Uint32 frame_time = SDL_GetTicks();
	Uint32 last_time = SDL_GetTicks();
	SDL_Event e;
	bool quit = false;

	float fps = 0;

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
	
	SDL_Rect rect = {10,10,20,20};

	SDL_FillRect( screenSurface, &rect, 0xffffffff);

	SDL_UpdateWindowSurface( window );


	while( !quit )
	{
		last_time = SDL_GetTicks();
	
		// Move rect
		rect.x += 1 * frame_time;

		SDL_FillRect( screenSurface, NULL, 0x00000000);
		SDL_FillRect( screenSurface, &rect, 0xffffffff);

		SDL_UpdateWindowSurface( window );

		if (rect.x > 800)
		{
			rect.x = 0;
		}
		
		while( SDL_PollEvent( &e ) )
		{ 
			if( e.type == SDL_QUIT ) quit = true; 
		} 
		
		frame_time = SDL_GetTicks() - last_time;
		fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
	}
	
	//Destroy window
	SDL_DestroyWindow( window );
	
	//Quit SDL subsystems
        SDL_Quit();
	
	return 0;
}
