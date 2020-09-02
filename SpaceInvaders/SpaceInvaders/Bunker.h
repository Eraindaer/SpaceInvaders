#pragma once
#include "GameObject.h"
class Bunker : public GameObject
{
public:
	Bunker();
	~Bunker();

	void Init(int x, int y, int w, int h) override;
	void Draw(Window* window);
	SDL_Rect src, dest;

private:
	int HP;

};

