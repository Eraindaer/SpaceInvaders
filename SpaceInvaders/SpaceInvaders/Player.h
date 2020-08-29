#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();

	int MoveX();
	int GetSpeed() { return speed; }
	void Update() override;
	void Fire();
	void Init(int x, int y, int w, int h) override;
	int GetHP() { return HP; }
	void Draw();
	void Damaged();
	void HealthBar();

	SDL_Rect src, src2, dest;
	SDL_Rect HPsrc, HPdest;
	SDL_Rect bulletSrc;
	Projectile* bullet;

	bool hit;
private:
	int speed = 7;
	int HP = 3;
};
