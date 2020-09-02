#include "Projectile.h"

Projectile::Projectile() {

}
Projectile::~Projectile() {
	dest.x = dest.y = dest.h = dest.w = 0;
	fire = false;
}

void Projectile::Init(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	fire = true;
}
void Projectile::Update(int direction, Window* window) {
	dest.y += direction * 7;
	if (dest.y < window->topBorder)
		Projectile::~Projectile();
}

void Projectile::Draw(SDL_Rect src, Window* window) {
	window->textureManager->DrawTexture(window->windowRenderer, src, dest);
}