#pragma once
#include "WindowManager.h"
class Menu
{
public:
	Menu();
	~Menu();

	void Init();
	void Update();
	void HandleEvents();
	void Render();
	void Clear();

private:
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
};

