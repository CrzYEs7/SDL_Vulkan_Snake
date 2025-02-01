#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Text
{
public:
    Text(char* font_name, char* content, int size, SDL_Color foreground_color, SDL_Color background_color);
    ~Text();
    void drawText(SDL_Surface* screen, int x, int y);

private:
	TTF_Font* m_font; // The font to be loaded from the ttf file.
	SDL_Surface* m_text_surface; // The surface necessary to create the font texture.
};

#endif
