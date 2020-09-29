#include "Game.h"


Game::Game() {
	player = new Player();
	enemyManager = new EnemyManager();
	bunkerManager = new BunkerManager();
	for (int i = 0; i < 4; i++)
		bunkerManager->Generator(i);

}

Game::~Game() {
	delete(player);
	delete(enemyManager);
	delete(bunkerManager);
}

///Initialisation du jeu, des différentes entités, préchargement des textures

void Game::Init(Window* window) {
	window->isRunning = true;
	window->scoreManager->SetScore(0);
	scoreDest.x = 650, scoreDest.y = 605;
	player->Init(370, 540, 45, 28);
	enemyManager->Initialisation();
	finish = false;
	for (int i = 0; i < 4; i++)
		bunkerManager->Initialisation(i);
}

///Gestion des évènements (quitter la fenêtre et tirer pour le moment)

void Game::HandleEvents(Window* window) {
	Scene::HandleEvents(window);
	player->Fire(window);
}

///Initialisation des déplacements

void Game::Update(Window* window) {
	if (enemyManager->GameLost(player))
		window->isRunning = false;
	player->Update(window);
	if (player->hit) {
		player->hit = false;
		SDL_Delay(1000);
	}
	if  (player->bullet != nullptr && player->bullet->fire) {
		player->bullet->Update(-1, window);
	}
	enemyManager->EnemyMissils();
	for (int i = 0; i < enemyManager->missilList.size(); i++) {
		if (enemyManager->missilList[i] != nullptr)
			enemyManager->missilList[i]->Update(1, window);
	}
	if (player->bullet != nullptr) {
		for (int i = 0; i < 4; i++)
			bunkerManager->Collision(i, player->bullet);
		enemyManager->Collision(player->bullet);
	}
	enemyManager->MissilHitPlayer(player);
	enemyManager->MissilDisappear(window);
	for (int i = 0; i < 4; i++) {
		bunkerManager->MissilCollision(i, enemyManager);
	}
	if (frame % (enemyManager->EnemyCounter()+5) == 0) {
		enemyManager->EnemyMovement(window);
		enemyMovement = (enemyMovement == 0) ? 1 : 0;
	}
	if (enemyManager->EnemyCounter() == 0) {
		enemyManager->Clear();
		Game::Restart();
	}
	frame++;
}

///Gestion des textures

void Game::Render(Window* window) {
	SDL_RenderClear(window->windowRenderer);
	if (player->bullet != nullptr && player->bullet->fire) {
		player->bullet->Draw(player->bulletSrc, window);
	}
	player->Draw(window);
	enemyManager->Draw(enemyMovement, window);
	for (int i = 0; i < 4; i++)
		bunkerManager->Draw(i, window);
	for (int j = 0; j < enemyManager->missilList.size(); j++) {
		enemyManager->missilList[j]->Draw(enemyManager->missilSrc, window);
	}
	player->HealthBar(window);
	window->textureManager->DrawCharacters(("SCORE  " + std::to_string(window->scoreManager->GetScore())).c_str(), window->windowRenderer, scoreDest);

	SDL_RenderPresent(window->windowRenderer);
	
}

///Regénération du niveau

void Game::Restart() {
	SDL_Delay(1000);
	enemyManager = new EnemyManager();
	enemyManager->Initialisation();
}