#pragma once
#include "SDL.h"
template <typename T, typename U>
bool KeyIsDown(T a, U b) {
	if (b->event.type == SDL_KEYDOWN && b->event.key.keysym.sym == a) {
		return true;
	}
	return false;
}

template <typename T, typename U>
bool KeyIsUp(T a, U b) {
	if (b->event.type == SDL_KEYUP && b->event.key.keysym.sym == a) {
		return true;
	}
	return false;
}

template <typename T, typename U>
void TextInput(T &a, U b) {
	if (b->event.type == SDL_KEYDOWN && !KeyIsDown(SDLK_BACKSPACE,b)) {
		if (((('a' <= b->event.key.keysym.sym) && ('z' >= b->event.key.keysym.sym)) || (('0' <= b->event.key.keysym.sym) && ('9' >= b->event.key.keysym.sym)) || b->event.key.keysym.sym == SDLK_SPACE) && a.length() <= 10)
			a += b->event.key.keysym.sym;
	}
	else if (a != "" && KeyIsDown(SDLK_BACKSPACE, b))
		a.pop_back();
}

