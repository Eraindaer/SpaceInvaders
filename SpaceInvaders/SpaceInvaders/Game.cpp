#include "Game.h"


Game::Game() {
	window = new Window();
	player = new Player();
	enemyManager = new EnemyManager();
	bunkerManager = new BunkerManager();
	for (int i = 0; i < 4; i++)
		bunkerManager->Generator(i);
}

Game::~Game() {
	delete(window);
	delete(player);
	delete(enemyManager);
	delete(bunkerManager);
}

///Initialisation du jeu, des différentes entités, préchargement des textures

void Game::Init() {
	window->Init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);
	player->Init(15, 540, 45, 28);
	enemyManager->Initialisation();
	finish = false;
	for (int i = 0; i < 4; i++)
		bunkerManager->Initialisation(i);
}

///Gestion des évènements (quitter la fenêtre et tirer pour le moment)

void Game::HandleEvents() {
	frameStart = SDL_GetTicks();
	window->FrameEvents();
	player->Fire(window);
}

///Initialisation des déplacements

void Game::Update() {
	player->Update(window);
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
		finish = true;
		enemyManager->Clear();
	}
	
	if (enemyManager->GameLost(player))
		window->isRunning = false;
	frame++;
}

///Gestion des textures

void Game::Render() {
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
	SDL_RenderPresent(window->windowRenderer);
}

///Fermeture de la fenêtre

void Game::Clear() {
	SDL_DestroyRenderer(window->windowRenderer);
	SDL_DestroyWindow(window->window);
	SDL_Quit();
}

///Gestion des délais

void Game::Delay() {
	if (player->hit) {
		player->hit = false;
		SDL_Delay(1000);
	}
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
}

///Regénération du niveau

void Game::Restart() {
	SDL_Delay(1000);
	enemyManager = new EnemyManager();
	enemyManager->Initialisation();
	finish = false;
}