#pragma once
#include "Entity.h"
class Health : public Entity
{
public:
	Health();
	~Health();
	char move(double time, char ent, maps& gamemap, COORD Player);
};

