#include "Player.h"

SDL_Event Window::event;
int Window::leftBorder, Window::rightBorder;
SDL_Texture* TextureManager::tex;


Player::Player() {
	Character();
	
}
Player::~Player() {

}

void Player::Init(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	src.x = HPsrc.x =  312;
	src.y = HPsrc.y = 3;
	src.w = HPsrc.w = 68;
	src.h = HPsrc.h = 42;
	src2.x = 383;
	src2.y = 2;
	src2.w = 79;
	src2.h = 43;
	bulletSrc.x = 409;
	bulletSrc.y = 48;
	bulletSrc.w = 23;
	bulletSrc.h = 46;
	hit = false;
}

int Player::MoveX() {
	int output = 0;
	if (Window::event.type == SDL_KEYDOWN) {
		switch (Window::event.key.keysym.sym)
		{
		case SDLK_LEFT:
			if(dest.x > Window::leftBorder + 10)
				output = -1;
			break;
		case SDLK_RIGHT:
			if(dest.x + dest.w < Window::rightBorder - 10)
				output = 1;
			break;
		default:
			break;
		}
	}
	else if (Window::event.type == SDL_KEYUP) {
		switch (Window::event.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
			output = 0;
			break;
		default:
			break;
		}
	}
	return output;
}

void Player::Update() {
	dest.x += Player::MoveX() * speed;
}
void Player::Fire() {
	if (Window::event.type == SDL_KEYDOWN) {
		switch (Window::event.key.keysym.sym)
		{
		case SDLK_SPACE:
		case SDLK_UP:
			if (bullet == nullptr || !bullet->fire) {
				bullet = new Projectile();
				bullet->Init(dest.x + 18, dest.y, 8, 24);
			}
			break;
		default:
			break;
		}
	}
}
void Player::Damaged() {
	HP--;
	hit = true;
}
void Player::HealthBar() {
	for (int i = 0; i < HP; i++) {
		HPdest.x = 10 + i * 55;
		HPdest.y = 600;
		HPdest.w = 51;
		HPdest.h = 32;
		TextureManager::DrawTexture(Window::windowRenderer, HPsrc, HPdest);
	}
}

void Player::Draw() {
	if (hit) {
		TextureManager::DrawTexture(Window::windowRenderer, src2, dest);
	}
	else
		TextureManager::DrawTexture(Window::windowRenderer, src, dest);
}