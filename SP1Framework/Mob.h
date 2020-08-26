#pragma once
#include "Entity.h"
class Mob : public Entity
{
public:
	Mob();
	~Mob();
	void spawnMob(int h, int m);
	char move(double time, char ent, maps& Gamemap, COORD Player);
};
