#pragma once
#include "TextureManager.h"
#include "WindowManager.h"
#include <vector>
#include <stdlib.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Init(int x, int y, int w, int h);
	virtual void Draw(Window* window, TextureManager* textureManager);
	virtual void Update();
	int X() { return xpos; }
	int Y() { return ypos; }
	int X(int x) { xpos = x; return xpos; }
	int Y(int y) { ypos = y; return ypos; }
	
    

private :
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect src, dest;
	
};

