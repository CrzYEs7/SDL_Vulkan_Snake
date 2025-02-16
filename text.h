#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Text
{
public:
    Text(SDL_Surface* surface, char* font_name, int size);
    ~Text();
    void drawText(SDL_Surface* display_surface, char* text, int x, int y, SDL_Color color);

private:
	TTF_Font* m_font; // The font to be loaded from the ttf file.
    SDL_Surface* m_surface; // where to draw the text
};

#endif
