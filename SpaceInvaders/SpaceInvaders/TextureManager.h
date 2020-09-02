#pragma once
#include "SDL.h"
#include "SDL_image.h"
class TextureManager {
public:
	SDL_Texture* tex;

	TextureManager();
	~TextureManager();

	void Init(const char* path, SDL_Renderer* renderer);
	void DrawTexture(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest);

};