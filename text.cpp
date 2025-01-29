#include "text.h"
#include <iostream>
#include "globals.h"

void Text::CreateText(const char* Message) 
{	
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(FONT_NAME, FONT_SIZE);
    if (!font)
        std::cout << "Couldn't find/init open ttf font." << std::endl;
    TextSurface = TTF_RenderText_Solid(font, Message, TextColor);
    TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    TextRect.x = SCREEN_SIZE - TextSurface->w * 0.5; // Center SCREEN_SIZETextRect.y = WINDOW_HEIGHT - TextSurface->h * 0.5; // Center verticaly
    TextRect.y = SCREEN_SIZE - TextSurface->h * 0.5; // Center verticaly
    TextRect.h = TextSurface->h;
    // After you create the texture you can release the surface memory allocation because we actually render the texture not the surface.
    SDL_FreeSurface(TextSurface);
    TTF_Quit();
}


void Text::RenderText() {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // Make window bg black.
    SDL_RenderClear(Renderer); // Paint screen black.
    SDL_RenderCopy(Renderer, TextTexture, NULL, &TextRect); // Add text to render queue.
    SDL_RenderPresent(Renderer); // Render everything that's on the queue.
    SDL_Delay(10); // Delay to prevent CPU overhead as suggested by the user `not2qubit`
}

void Text::ClearMemory() {
    SDL_DestroyTexture(TextTexture);
    SDL_DestroyRenderer(Renderer);
}
