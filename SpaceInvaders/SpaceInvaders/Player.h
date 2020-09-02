#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();

	int MoveX(Window* window);
	int GetSpeed() { return speed; }
	void Update(Window* window);
	void Fire(Window* window);
	void Init(int x, int y, int w, int h) override;
	int GetHP() { return HP; }
	void Draw(Window* window);
	void Damaged();
	void HealthBar(Window* window);

	SDL_Rect src, src2, dest;
	SDL_Rect HPsrc, HPdest;
	SDL_Rect bulletSrc;
	Projectile* bullet;

	bool hit;
private:
	int speed = 7;
	int HP = 3;
	int output;
};
