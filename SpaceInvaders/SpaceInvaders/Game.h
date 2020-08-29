#pragma once
#include "Player.h"
#include "EnemyManager.h"
#include "BunkerManager.h"
class Game {
public:
	Game();
	~Game();

	void Init();
	void Update();
	void HandleEvents();
	void Render();
	void Clear();
	void Delay();
	void Restart();
	bool isRunning(){ return Window::isRunning; }
	bool isFinished() { return finish; }

private:

	bool finish;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime; 
	Player* player;
	int frame = 0;
	int enemyMovement = 0;

};