#pragma once
#include <Windows.h>
#include "maps.h"

class Entity
{
protected:
	static int enemyTotal;
	static int count;
	int direction; //1 for left, 2 for right
	int hp, mp;
	int x, y;
	int id;
	COORD C;
public:
	Entity();
	~Entity();
	void spawnEntity(int h, int m);

	void setHP(int h);
	void setMP(int m);
	void setX(SHORT x);
	void setY(SHORT y);

	int getHP(void);
	int getMP(void);
	SHORT X(void);
	SHORT Y(void);
	COORD getXY(void);
	int getID(void);
	void addtomap(char add, maps& Gamemap);
	void move(char ent, maps& Gamemap);
	char collisioncheck(maps& gamemap);
};



