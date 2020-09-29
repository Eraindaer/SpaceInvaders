#include "Scene.h"
Scene::Scene() {
}
Scene::~Scene() {

}
void Scene::Init(Window* window) {
}
void Scene::Update(Window* window) {

}
void Scene::HandleEvents(Window* window) {
	frameStart = SDL_GetTicks();
	window->FrameEvents();
}
void Scene::Render(Window* window) {

}
void Scene::Delay() {
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
}
void Scene::Clear(Window* window) {
}
void Scene::Close(Window* window) {
	SDL_DestroyRenderer(window->windowRenderer);
	SDL_DestroyWindow(window->window);
	SDL_Quit();
}