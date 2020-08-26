#pragma once
#include "Entity.h"
class Mob : public Entity
{
public:
	Mob();
	~Mob();
	char move(double time, char ent, maps& Gamemap, COORD Player);
};
