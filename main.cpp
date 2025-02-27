#include <ostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_video.h"
#include "game.h"
#include "text.h"

/*
    TODO : When window resizing, the frame_time gets crazy, and the fruit timers miss berravier. (times passes really fast)
*/

int main(int argc, char* args[])
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        return 0;

   	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if( window == NULL )
		return EXIT_FAILURE; 

    SDL_Surface* canvas_surface = SDL_GetWindowSurface(window);
    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    
    Game game(window_surface);

    double frame_time = 0;
	double begin_frame_time = 0;
	double end_frame_time = 0;
    double fps = 0;
    double fps_limit = 1165;
	bool quit = false;

    int scaled_window_size_x = SCREEN_SIZE;
    int scaled_window_size_y = SCREEN_SIZE;

    SDL_Rect window_rect = {0,0,SCREEN_SIZE, SCREEN_SIZE};
    SDL_Rect scaled_window_rect = window_rect;

    Text fps_text = Text(canvas_surface, (char*)"NovaSquare-Regular.ttf", 10);

	while( !quit )
	{
		SDL_Event e;
		while( SDL_PollEvent( &e ) )
		{ 
			if(e.type == SDL_QUIT)
            {
				quit = true;
                break;
            }
            if (e.type == SDL_WINDOWEVENT)            {
                switch(e.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                        scaled_window_size_y = (int)e.window.data2;
                        scaled_window_size_x = (int)e.window.data1;

                        // Resize rect for surface and keep the ratio
                        // center rect for surface in the window 
                        if ( scaled_window_size_y <= scaled_window_size_x)
                        {
                            int black_bar_size = ((scaled_window_size_x - scaled_window_size_y) / 2);
                            scaled_window_rect = {(int)black_bar_size, 0, scaled_window_size_y, scaled_window_size_y};
                        }
                        else
                        {
                            int black_bar_size = ((scaled_window_size_y - scaled_window_size_x) / 2);
                            scaled_window_rect = {0, (int)black_bar_size, scaled_window_size_x, scaled_window_size_x};
                        }
                        
                        SDL_FreeSurface(window_surface);
                        SDL_FreeSurface(canvas_surface);
                        
                        // Surface resized
                        window_surface = SDL_GetWindowSurface(window);
                        
                        // Covert to 32bit color
                        canvas_surface = SDL_ConvertSurface(window_surface, window_surface->format, NULL);
                        break;
                }
            }
            //* ------------ Input ------------- *//
			game.Input(e);	
		}
		
		begin_frame_time = end_frame_time;

		//* ------------ Update --------- *//	
		game.Update(frame_time);	


		// Clear Screen
        // Color Format ARGB
		SDL_FillRect(canvas_surface, NULL, 0xff000000);
		SDL_FillRect(window_surface, NULL, 0xff000000);

        SDL_FillRect(canvas_surface, &window_rect, 0xff080808);

		/* ------------ Draw ----------- */	
		game.Draw(canvas_surface);

        fps_text.drawText(canvas_surface, (char*)(std::to_string((int)fps).c_str()), 10, 5, SDL_Color{0,255,0,255});

        if (SDL_BlitScaled(canvas_surface, &window_rect, window_surface, &scaled_window_rect) < 0)
        {
            printf("Error did not scale surface: %s\n", SDL_GetError());
        }
		
        SDL_UpdateWindowSurface( window );
		
        end_frame_time = SDL_GetPerformanceCounter();
        if ((end_frame_time - begin_frame_time) > 0)
		    frame_time = ((end_frame_time - begin_frame_time) * 1000.0f) / SDL_GetPerformanceFrequency();
        
        double delay = (1000.0f/fps_limit) - frame_time;
        if (delay > 0.0f)
            SDL_Delay(delay);
        if (frame_time > 0.0f)
            fps = SDL_round(1000 / frame_time);
        //printf("fps: %f\n", fps);
	}
	
	//Destroy window
	SDL_DestroyWindow( window );
	
	//Quit SDL subsystems
    SDL_Quit();
	
	return 0;
}
