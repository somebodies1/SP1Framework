#pragma once
#include "Entity.h"
class Mob : public Entity
{
public:
	Mob();
	~Mob();
	void spawnMob(int h, int m);
	
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);

	char move(double time, char ent, maps& Gamemap);
};
