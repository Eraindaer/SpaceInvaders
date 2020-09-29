#pragma once
#include "Player.h"
#include "EnemyManager.h"
#include "BunkerManager.h"
#include "Scene.h"
class Game : public Scene{
public:
	Game();
	~Game();

	void Init(Window* window) override;
	void Update(Window* window) override;
	void HandleEvents(Window* window) override;
	void Render(Window* window) override;
	void Restart();
	bool isRunning(Window* window) { return window->isRunning; }
	bool isFinished() { return finish; }

private:

	SDL_Rect scoreDest;
	EnemyManager* enemyManager;
	BunkerManager* bunkerManager;
	bool finish;
	Player* player;
	int currentScore;
	int frame = 0;
	int enemyMovement = 0;

};