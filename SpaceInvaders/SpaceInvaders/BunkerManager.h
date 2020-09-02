#pragma once
#include "Bunker.h"
#include "EnemyManager.h"
#include "Player.h"
#include <map>
class BunkerManager {
public :

	BunkerManager();
	~BunkerManager();

	void Generator(int bunkerNumber);
	void Initialisation(int bunkerNumber);
	void Collision(int bunkerNumber, Projectile* bullet);
	void MissilCollision(int bunkerNumber, EnemyManager* enemyManager);
	void Draw(int bunkerNumber, Window* window);

private :
	std::map<int, std::vector<std::vector<Bunker*>>> bunkerList;
	const bool bunkerMap[8][12] = 
	{ {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1} };
};