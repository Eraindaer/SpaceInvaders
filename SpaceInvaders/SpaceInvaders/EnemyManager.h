#pragma once
#include "Enemy.h"
#include "CollisionManager.h"
#include "Player.h"

class EnemyManager {
public:

	EnemyManager();
	~EnemyManager();

	void Initialisation();
	int EnemyCounter();
	void Collision(Projectile* bullet);

	void EnemyMovement(Window* window);
	void EnemyMissils();
	void MissilHitPlayer(Player* player);
	void MissilDisappear(Window* window);

	void Draw(int frame, Window* window);
	bool GameLost(Player* player);
	void Clear();

	SDL_Rect enemyGroupRect, missilSrc;
	std::vector<Projectile*> missilList;
private:
	bool movedToY;
	std::vector<std::vector<Enemy*>> enemyGroup;
	
};