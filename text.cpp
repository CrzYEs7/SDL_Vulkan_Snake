#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include "SDL2/SDL_surface.h"
#include "globals.h"
#include "text.h"

Text::Text(SDL_Surface* surface, char* font_name, int size)
{
    m_surface = surface;
    m_font = TTF_OpenFont(font_name , size);
    if (m_font == NULL)
        std::cout << "Font not created" << std::endl;
}

void Text::drawText(SDL_Surface* display_surface ,char* text, int x, int y, SDL_Color color)
{
    SDL_Surface* text_surface = TTF_RenderText_Blended(m_font, text, color);
    SDL_Rect text_location = { x, y, 0, 0 };
    SDL_BlitSurface(text_surface, NULL, display_surface, &text_location);
    SDL_FreeSurface(text_surface);
}

Text::~Text()
{
    TTF_CloseFont(m_font);
}
