#include "Player.h"

Player::Player() {	
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

int Player::MoveX(Window* window) {

	if (NoBorderCollision(dest, window)) {
		if (KeyIsDown(SDLK_LEFT, window))
			output = -1;
		else if (KeyIsUp(SDLK_LEFT, window))
			output = 0;

		if (KeyIsDown(SDLK_RIGHT, window))
			output = 1;
		else if (KeyIsUp(SDLK_RIGHT, window))
			output = 0;
	}
	else
		output *= -1;

	/*if (window->event.type == SDL_KEYDOWN) {
		switch (window->event.key.keysym.sym)
		{
		case SDLK_LEFT:
			if(dest.x > window->leftBorder + 10)
				output = -1;
			break;
		case SDLK_RIGHT:
			if(dest.x + dest.w < window->rightBorder - 10)
				output = 1;
			break;
		default:
			break;
		}
	}
	else if (window->event.type == SDL_KEYUP) {
		switch (window->event.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
			output = 0;
			break;
		default:
			break;
		}
	}*/
	return output;
}

void Player::Update(Window* window) {
	dest.x += Player::MoveX(window) * speed;
}
void Player::Fire(Window* window) {
	
	if (KeyIsDown(SDLK_UP, window) || KeyIsDown(SDLK_SPACE, window)) {
		if (bullet == nullptr || !bullet->fire) {
			bullet = new Projectile();
			bullet->Init(dest.x + 18, dest.y, 8, 24);
		}
	}
	
	/*if (window->event.type == SDL_KEYDOWN) {
		switch (window->event.key.keysym.sym)
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
	}*/
}
void Player::Damaged() {
	HP--;
	hit = true;
}
void Player::HealthBar(Window* window) {
	for (int i = 0; i < HP; i++) {
		HPdest.x = 90 + i * 55;
		HPdest.y = 600;
		HPdest.w = 51;
		HPdest.h = 32;
		window->textureManager->DrawTexture(window->windowRenderer, HPsrc, HPdest);
		textDest.x = 10, textDest.y = 610;
		window->textureManager->DrawCharacters("Lives", window->windowRenderer, textDest);
	}
	if (HP == 0) {
		window->textureManager->DrawCharacters("Game Over", window->windowRenderer, { 325, 300, 0, 0 });
		SDL_Delay(1000);
	}
}

void Player::Draw(Window* window) {
	if (hit) {
		window->textureManager->DrawTexture(window->windowRenderer, src2, dest);
	}
	else
		window->textureManager->DrawTexture(window->windowRenderer, src, dest);
}