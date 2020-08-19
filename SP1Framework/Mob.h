#pragma once
#include "Entity.h"
class Mob : public Entity
{
private:
	int hp, mp;
public:
	Mob();
	~Mob();
	void spawnMob(int h, int m);
	
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};


