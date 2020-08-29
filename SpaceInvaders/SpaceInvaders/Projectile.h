#pragma once
#include "GameObject.h"
class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	void Init(int x, int y, int w, int h);
	void Update(int direction);
	void Draw(SDL_Rect src);

	SDL_Rect dest;
	bool fire;
};

