#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "globals.h"
#include "game.h"
#include "text.h"

int main(int argc, char* args[])
{ 
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
		return 0;

	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN);
	if( window == NULL )
		return 0;

	SDL_Surface* screenSurface = SDL_GetWindowSurface( window );

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    Text text = Text((char*)"NovaSquare-Regular.ttf", (char*)"Press Enter to Start!", 38, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
    
    TTF_Font* font = TTF_OpenFont("NovaSquare-Regular.ttf", 30);
    SDL_Rect textLocation = { 100, 100, 0, 0 };
    SDL_Color foregroundColor = { 255, 255, 255 };
    SDL_Color backgroundColor = { 0, 0, 0, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "Press <Enter> to play!", foregroundColor, backgroundColor);
	
    Game game;
	
    float frame_time = 0;
	float last_time = 0;
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


		//* ------------ Draw ----------- *//	
		// Clear Screen
		SDL_FillRect( screenSurface, NULL, 0x00000000);
        
		game.Draw(screenSurface);

        //Text fps_text = Text((char*)"NovaSquare-Regular.ttf", (char*)(std::to_string(fps).c_str()) , 20, SDL_Color{0,255,0,255}, SDL_Color{0,0,0,0});
        //fps_text.drawText(screenSurface, (SCREEN_SIZE / 2) - 10, 5);

		SDL_UpdateWindowSurface( window );
		
		frame_time = SDL_GetTicks() - float(last_time);
		fps = (frame_time > 0.0f) ? 1000.0f / float(frame_time) : 0.0f;
		//printf("fps: %f\n", fps);
	}
	
	//Destroy window
	SDL_DestroyWindow( window );
	
	//Quit SDL subsystems
    SDL_Quit();
	
	return 0;
}
