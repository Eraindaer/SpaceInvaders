#include "TextureManager.h"

TextureManager::TextureManager() {
	fontSize = 25;
}
TextureManager::~TextureManager() {
	SDL_DestroyTexture(tex);
}

void TextureManager::Init(const char* path, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}
void TextureManager::InitFont(const char* path) {
	font = TTF_OpenFont(path, fontSize);
	color = { 255, 255, 255 };
}

void TextureManager::DrawTexture(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(renderer, tex, &src, &dest);
}

void TextureManager::DrawCharacters(const char* text, SDL_Renderer* renderer, SDL_Rect dest) {
	SDL_DestroyTexture(fontText);
  	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	fontText = SDL_CreateTextureFromSurface(renderer, textSurface);
	dest.w = textSurface->w, dest.h = textSurface->h;
	SDL_RenderCopy(renderer, fontText, NULL, &dest);
	SDL_FreeSurface(textSurface);
}