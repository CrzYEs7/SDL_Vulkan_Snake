#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include "globals.h"

#define MY_FONT "NovaSquare-Regular.ttf"

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Drawing Text", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE, SCREEN_SIZE, 0);

    if (!window){
        printf("Failed to open %d x %d window: %s\n", SCREEN_SIZE, SCREEN_SIZE, SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer){
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    TTF_Font *font = TTF_OpenFont(MY_FONT, 64);  // specify the path to your font file and font size

    if (!font){
        printf("Failed to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // Create surface with rendered text
    SDL_Color textColor = {0, 0, 0, 255}; // black color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello World!", textColor);

    if (!textSurface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // Create texture from surface
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (!textTexture){
        printf("Failed to create text texture: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Render text
    SDL_Rect textRect = {50, 50, textSurface->w, textSurface->h}; // rectangle where the text is drawn 
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}
