#pragma once
#include "Character.h"
class Enemy : public Character
{
public :
	Enemy();
	~Enemy();

	void Init(int x, int y, int w, int h) override;
	void MoveX();
	void MoveY();
	Projectile* Fire();
	void Draw(int x, int y, int w, int h, Window* window);
	SDL_Rect src, dest;
	SDL_Rect groupRect;
	int direction = 1;
	Projectile* missil;
	bool hit;
};

