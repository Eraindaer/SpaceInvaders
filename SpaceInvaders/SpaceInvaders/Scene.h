#pragma once
#include "WindowManager.h"
class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init(Window* window);
	virtual void Update(Window* window);
	virtual void HandleEvents(Window* window);
	virtual void Render(Window* window);
	void Delay();
	void Clear(Window* window);
	void Close(Window* window);
	bool isRunning(Window* window){ return window->isRunning; }
private:
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

};

