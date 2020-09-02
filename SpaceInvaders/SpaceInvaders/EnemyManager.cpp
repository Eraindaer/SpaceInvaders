#include "EnemyManager.h"

EnemyManager::EnemyManager() {
	bool enemyMap[5][11] =
	{ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
	for (int i = 0; i < 5; i++) {
		std::vector<Enemy*> enemyRow;
		for (int j = 0; j < 11; j++) {
			if (enemyMap[i][j] != 0)
				enemyRow.push_back(new Enemy());
			else
				enemyRow.push_back(nullptr);
		}
		enemyGroup.push_back(enemyRow);
	}
}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Initialisation() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			if (enemyGroup[i][j] != nullptr)
				enemyGroup[i][j]->Init(10 + j * 50, 10 + i * 40, 45, 30);
		}
	}
	missilSrc.x = 383;
	missilSrc.y = 47;
	missilSrc.w = 23;
	missilSrc.h = 46;
	movedToY = true;
}
int EnemyManager::EnemyCounter() {
	int enemyNumber = 0;
	for (int i = 0; i < enemyGroup.size(); i++) {
		for (int j = 0; j < enemyGroup[i].size(); j++) {
			if (enemyGroup[i][j] != nullptr) {
				enemyNumber++;
			}
		}
	}
	return enemyNumber;
}
void EnemyManager::Collision(Projectile* bullet) {
	for (int i = 0; i < enemyGroup.size(); i++) {
		for (int j = 0; j < enemyGroup[i].size(); j++) {
			if (enemyGroup[i][j] != nullptr && CollisionAABB(bullet, enemyGroup[i][j])) {
				enemyGroup[i][j]->hit = true;
				bullet->~Projectile();
			}
		}
	}
	bullet = nullptr;
}
void EnemyManager::EnemyMovement(Window* window) {
	enemyGroupRect.x = enemyGroupRect.y = enemyGroupRect.h = enemyGroupRect.w = 0;
	//Construction du rectangle autour des ennemis
	///Explications :
	/// __________________________________
	/// | ennemi  ennemi  ennemi  ennemi  |
	/// | ennemi  ennemi  ennemi  ennemi  |
	/// | ennemi  ennemi  ennemi  ennemi  |
	/// | ennemi  ennemi  ennemi  ennemi  |
	/// | ennemi  ennemi  ennemi  ennemi  |
	///	|_________________________________|
	/////////////////////////////////////////////////
	for (int i = 0; i < enemyGroup.size(); i++) {
		for (int j = 0; j < enemyGroup[i].size(); j++) {
			if (enemyGroup[i][j] != nullptr) {
				if (enemyGroupRect.x == 0 && enemyGroupRect.y == 0 && enemyGroupRect.h == 0 && enemyGroupRect.w == 0) {
					enemyGroupRect.x = enemyGroup[i][j]->dest.x;
					enemyGroupRect.y = enemyGroup[i][j]->dest.y;
					enemyGroupRect.h = enemyGroup[i][j]->dest.h;
					enemyGroupRect.w = enemyGroup[i][j]->dest.w;
				}
				if (enemyGroupRect.x > enemyGroup[i][j]->dest.x) {
					enemyGroupRect.x = enemyGroup[i][j]->dest.x;
				}
				if (enemyGroupRect.y > enemyGroup[i][j]->dest.y) {
					enemyGroupRect.y = enemyGroup[i][j]->dest.y;
				}
				if (enemyGroupRect.h < (enemyGroup[i][j]->dest.y + enemyGroup[i][j]->dest.h) - enemyGroupRect.y) {
					enemyGroupRect.h = enemyGroup[i][j]->dest.y - enemyGroupRect.y + enemyGroup[i][j]->dest.h;
				}
				if (enemyGroupRect.w < (enemyGroup[i][j]->dest.x + enemyGroup[i][j]->dest.w) - enemyGroupRect.x) {
					enemyGroupRect.w = enemyGroup[i][j]->dest.x - enemyGroupRect.x + enemyGroup[i][j]->dest.w;
				}
			}
		}
	}

	if ((movedToY) || (enemyGroupRect.x > window->leftBorder + 10 && enemyGroupRect.x + enemyGroupRect.w < window->rightBorder - 10)) {
		for (int k = 0; k < enemyGroup.size(); k++) {
			for (int h = 0; h < enemyGroup[k].size(); h++) {
				if (enemyGroup[k][h] != nullptr) {
					enemyGroup[k][h]->MoveX();
				}
			}
		}
		movedToY = false;
	}
	else if (!movedToY) {
		for (int k = 0; k < enemyGroup.size(); k++) {
			for (int h = 0; h < enemyGroup[k].size(); h++) {
				if (enemyGroup[k][h] != nullptr) {
					enemyGroup[k][h]->MoveY();
					enemyGroup[k][h]->direction *= -1;
				}
			}
		}
		movedToY = true;
	}
}
void EnemyManager::EnemyMissils() {
	for (int i = 0; i < enemyGroup.size(); i++) {
		for (int j = 0; j < enemyGroup[i].size(); j++) {
			if (enemyGroup[i][j] != nullptr && rand() % (int)(EnemyManager::EnemyCounter() * 10) == 1 && missilList.size() <= 5) {
				missilList.push_back(enemyGroup[i][j]->Fire());
			}
		}
	}
}
void EnemyManager::MissilHitPlayer(Player* player) {
	for (int i = 0; i < missilList.size(); i++) {
		if (missilList[i] != nullptr && CollisionAABB(missilList[i], player)) {
			delete(missilList[i]);
			missilList.erase(missilList.begin() + i);
			player->Damaged();
		}
	}
}
void EnemyManager::MissilDisappear(Window* window) {
	for (int i = 0; i < missilList.size(); i++)
		if (missilList[i]->dest.y > window->bottomBorder) {
			missilList[i]->~Projectile();
			missilList.erase(missilList.begin() + i);
		}
}

void EnemyManager::Draw(int frame, Window* window) {
	for (int i = 0; i < enemyGroup.size(); i++)
		for (int j = 0; j < enemyGroup[i].size(); j++) {
			if (enemyGroup[i][j] != nullptr)
				if (enemyGroup[i][j]->hit) {
					enemyGroup[i][j]->Draw(310, 49, 69, 44, window);
					delete(enemyGroup[i][j]);
					enemyGroup[i][j] = nullptr;
				}
				else
					switch (i)
					{
					case 0:
						enemyGroup[i][j]->Draw(177 + frame * 71, 76, 50, 50, window);
						break;
					case 1:
					case 2:
						enemyGroup[i][j]->Draw(12 + frame * 83, 76, 68, 50, window);
						break;
					default:
						enemyGroup[i][j]->Draw(128 + frame * 88, 12, 75, 50, window);
						break;
					}

		}
}
bool EnemyManager::GameLost(Player* player) {
	if (enemyGroupRect.y + enemyGroupRect.h >= 450 || player->GetHP() <= 0)
		return true;
	return false;
}
void EnemyManager::Clear() {
	enemyGroup.clear();
}