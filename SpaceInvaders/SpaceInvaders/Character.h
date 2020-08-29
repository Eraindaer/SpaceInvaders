#pragma once
#include "Entity.h"
#include "Projectile.h"
class Character : public Entity
{
public:
	Character();
	~Character();

	void Update() override;


};

