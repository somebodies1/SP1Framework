#pragma once
#include "Entity.h"
class Boss :
	public Entity
{
private:
	int hp, mp;
public:
	Boss();
	~Boss();
	void spawnBoss(int h, int m);
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};

class Boss :
	public Entity
{
};

