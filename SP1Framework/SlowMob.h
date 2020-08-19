#pragma once
#include "Entity.h"
class SlowMob : public Entity
{
private:
	int hp, mp;
public:
	SlowMob();
	~SlowMob();
	void spawnSlowMob(int h, int m);
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};

class SlowMob :
	public Entity
{
};

