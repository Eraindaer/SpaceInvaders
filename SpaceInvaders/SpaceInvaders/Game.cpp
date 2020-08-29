#include "Game.h"

bool Window::isRunning;
SDL_Renderer* Window::windowRenderer;
SDL_Window* Window::window;

SDL_Rect EnemyManager::enemyGroupRect, EnemyManager::missilSrc;
bool EnemyManager::movedToY;
std::vector<std::vector<Enemy*>> EnemyManager::enemyGroup;

std::map<int, std::vector<std::vector<Bunker*>>> BunkerManager::bunkerList;

std::vector<Projectile*> EnemyManager::missilList;

int enemyMap[5][11] =
{ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int bunkerMap[8][12] =
{ {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1}};


Game::Game() {
	player = new Player();
	EnemyManager::EnemyVectorGenerator(enemyMap);
	for(int i = 0; i < 4; i++)
		BunkerManager::BunkerVectorGenerator(bunkerMap, i);
}

Game::~Game() {

}

///Initialisation du jeu

void Game::Init() {
	Window::Init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);
	player->Init(15, 540, 45, 28);
	EnemyManager::Initialisation();
	TextureManager::InitTexture("assets/spaceI.png", Window::windowRenderer);
	finish = false;
	for (int i = 0; i < 4; i++)
		BunkerManager::Initialisation(i);
}

void Game::HandleEvents() {
	frameStart = SDL_GetTicks();
	Window::FrameEvents();
	player->Fire();
}

///Initialisation des déplacements

void Game::Update() {
	player->Update();
	if  (player->bullet != nullptr && player->bullet->fire) {
		player->bullet->Update(-1);
	}
	EnemyManager::EnemyMissils();
	for (int i = 0; i < EnemyManager::missilList.size(); i++) {
		if (EnemyManager::missilList[i] != nullptr)
			EnemyManager::missilList[i]->Update(1);
	}
	if (player->bullet != nullptr) {
		for (int i = 0; i < 4; i++)
			BunkerManager::Collision(i, player->bullet);
		EnemyManager::Collision(player->bullet);
	}
	EnemyManager::MissilHitPlayer(player);
	EnemyManager::MissilDisappear();
	for (int i = 0; i < 4; i++) {
		BunkerManager::MissilCollision(i);
	}
	if (frame % (EnemyManager::EnemyCounter()+5) == 0) {
		EnemyManager::EnemyMovement();
		enemyMovement = (enemyMovement == 0) ? 1 : 0;
	}
	if (EnemyManager::EnemyCounter() == 0) {
		finish = true;
		EnemyManager::Clear();
	}
	
	if (EnemyManager::GameLost(player))
		Window::isRunning = false;
	frame++;
}

///Gestion des textures

void Game::Render() {
	SDL_RenderClear(Window::windowRenderer);
	if (player->bullet != nullptr && player->bullet->fire) {
		player->bullet->Draw(player->bulletSrc);
	}
	player->Draw();
	EnemyManager::Draw(enemyMovement);
	for (int i = 0; i < 4; i++)
		BunkerManager::Draw(i);
	for (int j = 0; j < EnemyManager::missilList.size(); j++) {
		EnemyManager::missilList[j]->Draw(EnemyManager::missilSrc);
	}
	player->HealthBar();
	SDL_RenderPresent(Window::windowRenderer);

}
void Game::Clear() {
	SDL_DestroyRenderer(Window::windowRenderer);
	SDL_DestroyWindow(Window::window);
	SDL_Quit();
}

void Game::Delay() {
	if (player->hit) {
		player->hit = false;
		SDL_Delay(1000);
	}
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
}

void Game::Restart() {
	SDL_Delay(1000);
	EnemyManager::EnemyVectorGenerator(enemyMap);
	EnemyManager::Initialisation();
	finish = false;
}