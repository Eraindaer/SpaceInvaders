#include "TextureManager.h"

TextureManager::TextureManager() {
	
}
TextureManager::~TextureManager() {
}

void TextureManager::Init(const char* path, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void TextureManager::DrawTexture(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(renderer, tex, &src, &dest);
}