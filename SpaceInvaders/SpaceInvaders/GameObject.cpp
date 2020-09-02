#include "GameObject.h"
GameObject::GameObject() {
	Window::Window();
	xpos = ypos = 0;
	width = height = 32;
	GameObject::Init(xpos, ypos, height, width);
}

GameObject::~GameObject() {

}

void GameObject::Init(int x, int y, int h, int w) {
}

void GameObject::Update() {
}

void GameObject::Draw(Window* window, TextureManager* textureManager){
	textureManager->DrawTexture(window->windowRenderer, src, dest);
}


