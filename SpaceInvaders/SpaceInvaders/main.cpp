#include "Game.h"

Game* game = new Game();

int main(int argc, char* argv[]) {

	game->Init();	

	while (game->isRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
		game->Delay();
		if (game->isFinished())
			game->Restart();
	}
	game->Clear();
	return 0;
}