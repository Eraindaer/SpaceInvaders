#pragma once
#include "Bunker.h"
#include "EnemyManager.h"
#include "Player.h"
#include <map>
class BunkerManager {
public :

	static void BunkerVectorGenerator(int bunkerMap[8][12], int bunkerNumber) {
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
	static void Initialisation(int bunkerNumber) {
		
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
	static void Collision(int bunkerNumber, Projectile* bullet) {
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
	static void MissilCollision(int bunkerNumber) {
		for (int i = 0; i < bunkerList[bunkerNumber].size(); i++) {
			for (int j = 0; j < bunkerList[bunkerNumber][i].size(); j++) {
				for (int k = 0; k < EnemyManager::missilList.size(); k++) {
					if (EnemyManager::missilList[k] != nullptr && 
						bunkerList[bunkerNumber][i][j] != nullptr && 
						CollisionAABB(EnemyManager::missilList[k], bunkerList[bunkerNumber][i][j])) {
						bunkerList[bunkerNumber][i][j]->~Bunker();
						EnemyManager::missilList[k]->~Projectile();
						EnemyManager::missilList.erase(EnemyManager::missilList.begin()+k);
					}
				}
			}
		}
	}
	static void Draw(int bunkerNumber) {
		for (int i = 0; i < bunkerList[bunkerNumber].size(); i++) {
			for (int j = 0; j < bunkerList[bunkerNumber][i].size(); j++) {
				if (bunkerList[bunkerNumber][i][j] != nullptr) {
					bunkerList[bunkerNumber][i][j]->Draw();
				}
			}
		}
	}
private :
	static std::map<int, std::vector<std::vector<Bunker*>>> bunkerList;
};