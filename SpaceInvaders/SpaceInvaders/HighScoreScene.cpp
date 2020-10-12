#include "HighScoreScene.h"

HighScoreScene::HighScoreScene() {
	text = "";
	frame = 0;
	enterName = true;
}

HighScoreScene::~HighScoreScene() {

}

void HighScoreScene::Init(Window* window) {
	window->isRunning = true;
	fileManager = new FileManager();
	SDL_StartTextInput();
}

void HighScoreScene::Update(Window* window) {
	if (frame % 40 == 0) {
		pressVisible = !pressVisible;
		frame = 1;
	}
	frame++;
}

void HighScoreScene::HandleEvents(Window* window) {
	Scene::HandleEvents(window);	
	TextInput(text, window);

	if (enterName && KeyIsDown(SDLK_RETURN, window)) {
		fileManager->SetClassment("assets/highScore.txt", text, window->scoreManager->GetScore());
		enterName = false;
	}

	if (!enterName && KeyIsDown(SDLK_ESCAPE, window)) {
		fileManager->Write("assets/highScore.txt");
		window->isRunning = false;
		window->finish = true;
	}
	else if (!enterName && KeyIsDown(SDLK_F1, window)) {
		fileManager->Write("assets/highScore.txt");
		window->isRunning = false;
	}
}
void HighScoreScene::Render(Window* window) {
	SDL_RenderClear(window->windowRenderer);
	if (enterName) {
		window->textureManager->DrawCharacters("Enter     your      name ", window->windowRenderer, { 275, 150, 0, 0 });
		if (text != "")
			window->textureManager->DrawCharacters(text.c_str(), window->windowRenderer, { 325, 200, 0, 0 });
	}
	else {
		int line = 0;
		for (auto const& entry : fileManager->GetClassment()) {
			if (line < 10) {
				window->textureManager->DrawCharacters(std::to_string(line + 1).c_str(), window->windowRenderer, { 150, 50 + 50 * line, 0, 0 });
				window->textureManager->DrawCharacters(entry.second.c_str(), window->windowRenderer, { 200, 50 + 50 * line, 0, 0 });
				window->textureManager->DrawCharacters(std::to_string(entry.first).c_str(), window->windowRenderer, { 600, 50 + 50 * line, 0,0 });
			}
			line++;
		}
		if (pressVisible) {
			window->textureManager->DrawCharacters("Press     ESCPAPE     to     exit", window->windowRenderer, { 500, 600, 0,0 });
			window->textureManager->DrawCharacters("Press     F1      to       try     again", window->windowRenderer, { 10, 600,0,0 });
		}

	}
	SDL_RenderPresent(window->windowRenderer);
}