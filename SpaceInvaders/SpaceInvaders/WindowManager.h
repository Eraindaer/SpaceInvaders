#pragma once
#ifndef WINDOWMANAGER_HEADER
#define WINDOWMANAGER_HEADER
#include "TextureManager.h"
#include "ScoreManager.h"

class Window {
public:
	Window();
	~Window();
	void Init(const char* title, int xpos, int ypos, int width, int height);
	void FrameEvents();
	
	SDL_Event event;
	bool isRunning, finish;
	SDL_Renderer* windowRenderer;
	SDL_Window* window;
	TextureManager* textureManager;
	ScoreManager* scoreManager;
	int leftBorder, rightBorder, topBorder, bottomBorder;
};	
#endif 