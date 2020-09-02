#include "Enemy.h"


Enemy::Enemy() {

}
Enemy::~Enemy() {
	dest.h = dest.w = 0;
	dest.x = 300;
	dest.y = -100;
}
void Enemy::Init(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	hit = false;
}

void Enemy::MoveX() {
	dest.x += dest.w/2 * direction;
}
void Enemy::MoveY() {
	dest.y += dest.w/2;
}

Projectile* Enemy::Fire() {
	missil = new Projectile();
	missil->Init(dest.x + dest.w / 2, dest.y + dest.h, 8, 24);
	return missil;
}

void Enemy::Draw(int x, int y, int w, int h, Window* window) {
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
	window->textureManager->DrawTexture(window->windowRenderer, src, dest);
}