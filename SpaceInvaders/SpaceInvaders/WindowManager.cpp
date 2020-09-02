#include "WindowManager.h"

Window::Window() {
	textureManager = new TextureManager();
}
Window::~Window() {
	delete(textureManager);
}

void Window::Init(const char* title, int xpos, int ypos, int width, int height) {
	leftBorder = topBorder = 0;
	rightBorder = width;
	bottomBorder = height;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
		windowRenderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 255);
		isRunning = true;
	}
	else
		isRunning = false;
	textureManager->Init("assets/spaceI.png", windowRenderer);
}
void Window::FrameEvents() {

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}
}