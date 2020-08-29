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
void Projectile::Update(int direction) {
	dest.y += direction * 7;
	if (dest.y < Window::topBorder)
		Projectile::~Projectile();
}

void Projectile::Draw(SDL_Rect src) {
	TextureManager::DrawTexture(Window::windowRenderer, src, dest);
}