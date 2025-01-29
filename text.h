#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> //This is an sample library not included with stock SDL2. https://www.libsdl.org/projects/SDL_ttf/release-1.2.html

class Text
{
public:
	void CreateText(const char* Message);	
	void RenderText();
	void ClearMemory();
	SDL_Renderer* Renderer;// The renderer that shows our textures.

private:
	const char* FONT_NAME = "NovaSquare-Regular.ttf";
	const int FONT_SIZE = 128;
	SDL_Color TextColor = { 255, 0, 0, 255}; // Red SDL color.
	TTF_Font* Font; // The font to be loaded from the ttf file.
	SDL_Surface* TextSurface; // The surface necessary to create the font texture.
	SDL_Texture* TextTexture; // The font texture prepared for render.
	SDL_Rect TextRect; // Text rectangle area with the position for the texture text.
};

#endif
