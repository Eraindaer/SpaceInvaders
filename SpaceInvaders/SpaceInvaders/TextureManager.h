#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
class TextureManager {
public:
	SDL_Texture* tex;
	SDL_Texture* fontText;
	SDL_Color color;
	TTF_Font* font;

	TextureManager();
	~TextureManager();

	void Init(const char* path, SDL_Renderer* renderer);
	void InitFont(const char* path);
	void DrawTexture(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest);
	void DrawCharacters(const char* score, SDL_Renderer* renderer, SDL_Rect dest);

private:
	int fontSize;
};