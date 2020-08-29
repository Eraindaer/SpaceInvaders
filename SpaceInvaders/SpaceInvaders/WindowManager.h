#pragma once
#ifndef WINDOWMANAGER_HEADER
#define WINDOWMANAGER_HEADER
#include "TextureManager.h"

class Window {
public:
	Window() {
	}
	~Window() {
	}
	static SDL_Event event;
	static bool isRunning;
	static SDL_Renderer* windowRenderer;
	static SDL_Window* window;
	static int leftBorder, rightBorder, topBorder, bottomBorder;

	static void Init(const char* title, int xpos, int ypos, int width, int height) {
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
	}
	static void FrameEvents() {
		
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT :
			isRunning = false;
		default:
			break;
		}
	}

};	
#endif 