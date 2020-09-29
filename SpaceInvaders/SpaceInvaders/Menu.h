#pragma once
#include "InputManager.h"
#include "Scene.h"
class Menu : public Scene
{
public:
	Menu();
	~Menu();

	void Init(Window* window) override;
	void Update(Window* window) override;
	void HandleEvents(Window* window) override;
	void Render(Window* window) override;

protected:
	int frame;
	bool pressVisible;
	SDL_Rect srcTitle, destTitle, srcPress, destPress;
};

