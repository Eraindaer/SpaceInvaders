#pragma once
#include "Scene.h"
#include "InputManager.h"
#include "FileManager.h"
class HighScoreScene : public Scene
{
public:
	HighScoreScene();
	~HighScoreScene();
	
	void Init(Window* window) override;
	void Update(Window* window) override;
	void HandleEvents(Window* window) override;
	void Render(Window* window) override;

private:
	std::string text;
	SDL_Rect srcForm, destForm;
	int frame;
	Uint32 timer, timerStart;
	bool enterName, pressVisible;
	FileManager* fileManager;
};

