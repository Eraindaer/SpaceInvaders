#include "Menu.h"
Menu::Menu() {
	srcTitle.x = 88, srcTitle.y = 253, srcTitle.w = 800, srcTitle.h = 470;

	destTitle.x = 100, destTitle.y = 75, destTitle.w = 0.75 * srcTitle.w, destTitle.h = 0.75 * srcTitle.h;
	destPress.x = 230, destPress.y = 500;

	pressVisible = true;
}
Menu::~Menu() {
	
}
void Menu::Init(Window* window) {
	window->isRunning = true;
}
void Menu::Update(Window* window) {
	if (frame % 40 == 0) {
		pressVisible = !pressVisible;
		frame = 1;
	}
	frame++;
}
void Menu::HandleEvents(Window* window) {
	Scene::HandleEvents(window);
	if (KeyIsDown(SDLK_SPACE, window))
		window->isRunning = false;
}
void Menu::Render(Window* window) {
	SDL_RenderClear(window->windowRenderer);
	window->textureManager->DrawTexture(window->windowRenderer, srcTitle, destTitle);
	if (pressVisible)
		window->textureManager->DrawCharacters("Press       SPACEBAR         to       start", window->windowRenderer, destPress);
	SDL_RenderPresent(window->windowRenderer);
}
