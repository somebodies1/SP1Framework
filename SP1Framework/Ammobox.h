#pragma once
#include "Entity.h"
class Ammobox : public Entity
{
public:
	Ammobox();
	~Ammobox();
	char move(double time, char ent, maps& gamemap, COORD Player);
};

