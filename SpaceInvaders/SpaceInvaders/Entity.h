#pragma once
#include "GameObject.h"
class Entity : public GameObject
{
public :
	Entity();
	~Entity();

	int GetHP() { return HP; }

private:
	int HP;
};

