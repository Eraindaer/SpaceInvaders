#include "Bunker.h"

Bunker::Bunker() {
	HP = 3;
}
Bunker::~Bunker(){
	dest.h = dest.w = 0;
	dest.x = Window::rightBorder / 2;
	dest.y = -100;
}

void Bunker::Init(int x, int y, int w, int h){
	src.x = 321;
	src.y = 106;
	src.w = 10;
	src.h = 10;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}

void Bunker::Draw() {
	TextureManager::DrawTexture(Window::windowRenderer, src, dest);
}