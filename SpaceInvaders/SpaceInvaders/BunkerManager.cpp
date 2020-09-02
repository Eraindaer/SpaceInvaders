#include "BunkerManager.h"

BunkerManager::BunkerManager() {
}

BunkerManager::~BunkerManager() {
	
}

void BunkerManager::Generator(int bunkerNumber) {
	for (int i = 0; i < 8; i++) {
		std::vector<Bunker*> bunkerRow;
		for (int j = 0; j < 12; j++) {
			if (bunkerMap[i][j] != 0)
				bunkerRow.push_back(new Bunker());
			else
				bunkerRow.push_back(nullptr);
		}
		bunkerList[bunkerNumber].push_back(bunkerRow);
	}
}

void BunkerManager::Initialisation(int bunkerNumber) {
	for (int i = 0; i < bunkerList[bunkerNumber].size(); i++)
	{
		for (int j = 0; j < bunkerList[bunkerNumber][i].size(); j++)
		{
			if (bunkerList[bunkerNumber][i][j] != nullptr) {
				bunkerList[bunkerNumber][i][j]->Init(175 * bunkerNumber + 75 + j * 9, 450 + i * 9, 9, 9);
			}
		}
	}
}

void BunkerManager::Collision(int bunkerNumber, Projectile* bullet) {
	for (int i = 0; i < bunkerList[bunkerNumber].size(); i++) {
		for (int j = 0; j < bunkerList[bunkerNumber][i].size(); j++) {
			if (bunkerList[bunkerNumber][i][j] != nullptr && CollisionAABB(bullet, bunkerList[bunkerNumber][i][j])) {
				bunkerList[bunkerNumber][i][j]->~Bunker();
				bullet->~Projectile();
			}
		}
	}
	bullet = nullptr;
}
void BunkerManager::MissilCollision(int bunkerNumber, EnemyManager* enemyManager) {
	for (int i = 0; i < bunkerList[bunkerNumber].size(); i++) {
		for (int j = 0; j < bunkerList[bunkerNumber][i].size(); j++) {
			for (int k = 0; k < enemyManager->missilList.size(); k++) {
				if (enemyManager->missilList[k] != nullptr &&
					bunkerList[bunkerNumber][i][j] != nullptr &&
					CollisionAABB(enemyManager->missilList[k], bunkerList[bunkerNumber][i][j])) {
					bunkerList[bunkerNumber][i][j]->~Bunker();
					enemyManager->missilList[k]->~Projectile();
					enemyManager->missilList.erase(enemyManager->missilList.begin() + k);
				}
			}
		}
	}
}
void BunkerManager::Draw(int bunkerNumber, Window* window) {
	for (int i = 0; i < bunkerList[bunkerNumber].size(); i++) {
		for (int j = 0; j < bunkerList[bunkerNumber][i].size(); j++) {
			if (bunkerList[bunkerNumber][i][j] != nullptr) {
				bunkerList[bunkerNumber][i][j]->Draw(window);
			}
		}
	}
}