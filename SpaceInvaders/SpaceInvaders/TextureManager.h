#pragma once
#include "SDL.h"
#include "SDL_image.h"
class TextureManager {
public:
	static SDL_Texture* tex;
	static void InitTexture(const char* path, SDL_Renderer* renderer) {
		SDL_Surface* tempSurface = IMG_Load("assets/spaceI.png");
		tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
	static void DrawTexture(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest){	
		SDL_RenderCopy(renderer, tex, &src, &dest);
	}

};