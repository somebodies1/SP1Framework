#pragma once
#include "Entity.h"
class SlowMob : public Entity
{
private:

public:
	SlowMob();
	~SlowMob();
	void spawnSlowMob(int h, int m);
	char move(double time, char ent, maps& gamemap);
};

