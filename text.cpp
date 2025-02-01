#include "text.h"
#include <SDL2/SDL_ttf.h>
#include <ostream>
#include "globals.h"


Text::Text(char* font_name, char* content, int size, SDL_Color foreground_color, SDL_Color background_color)
{
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
    }

    m_font = TTF_OpenFont(font_name , size);
    if (m_font == NULL)
        std::cout << "Font not created" << std::endl;
    m_text_surface = TTF_RenderText_Shaded(m_font, content, foreground_color, background_color);
}

void Text::drawText(SDL_Surface* screen, int x, int y)
{
    SDL_Rect text_location = { x, y, 0, 0 };
    SDL_BlitSurface(m_text_surface, NULL, screen, &text_location);
}

Text::~Text()
{
    std::cout << "text drestroyed" << std::endl;
    SDL_FreeSurface(m_text_surface);
    TTF_CloseFont(m_font);
}
