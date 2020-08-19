#pragma once
#include "Entity.h"
class SpeedyMob :
	public Entity
{
private:
	int hp, mp;
public:
	SpeedyMob();
	~SpeedyMob();
	void spawnSpeedyMob(int h, int m);
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};

class SpeedyMob :
	public Entity
{
};

