#pragma once
#include "Entity.h"
class StationaryMob :
	public Entity
{
private:
	int hp, mp;
public:
	StationaryMob();
	~StationaryMob();

	void spawnStationaryMob(int h, int m);
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};

