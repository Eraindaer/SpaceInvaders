#include "SceneManager.h"

//Initilisation de la fenêtre et des différentes scènes
Window* window = new Window();
Scene* array[] = { new Game(), new HighScoreScene() };
Scene* currentScene = new Menu();

int main(int argc, char* argv[]) { 
	window->Init("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);
	int i = 0;
	while (!window->finish) {
		if (currentScene != NULL) {
			currentScene->Init(window);
			while (currentScene->isRunning(window)) {
				//Déroulement d'une frame
				currentScene->HandleEvents(window);
				currentScene->Update(window);
				currentScene->Render(window);
				currentScene->Delay();
			}
			if (window->finish) {
				currentScene = NULL;
			}
			if (i % 2 != 1)
				currentScene = new Game();
			else
				currentScene = new HighScoreScene();
			i++;
		}
	}
	currentScene->Clear(window);
	currentScene->Close(window);
	return 0;
}