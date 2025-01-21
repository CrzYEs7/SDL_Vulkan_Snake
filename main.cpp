#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* args[])
{
	printf("Hello there");
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	Uint32 frame_time = SDL_GetTicks();
	Uint32 last_time = SDL_GetTicks();

	float fps = 0;

	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL not initialized! SDL_Error:%n\n", SDL_GetError());
		return 0;
	}

	
	window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}
	
	screenSurface = SDL_GetWindowSurface( window );
	
	SDL_Rect rect = SDL_Rect();
	rect.x = 10;
	rect.y = 10;
	rect.w = 20;
	rect.h = 20;

	SDL_FillRect( screenSurface, &rect, 0xffffffff);

	SDL_UpdateWindowSurface( window );

	SDL_Event e;
	bool quit = false;
	while( !quit )
	{
		last_time = SDL_GetTicks();
		rect.x += 1 * frame_time;
		printf("fps : %f\n", fps);
		printf("rect x %i\n", rect.x);

		SDL_FillRect( screenSurface, NULL, 0x00000000);
		SDL_FillRect( screenSurface, &rect, 0xffffffff);

		SDL_UpdateWindowSurface( window );

		if (rect.x > 800)
		{
			rect.x = 0;
		}
		while( SDL_PollEvent( &e ) )
		{ 
			printf("rolling");
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
