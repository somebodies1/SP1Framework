#pragma once
#include <Windows.h>
#include "maps.h"

class Entity
{
protected:
	char type;
	static int score;
	static int enemyTotal;
	static int count;
	int direction; //1 for left, 2 for right
	int hp;
	static int mp;
	int x, y;
	int id;
	COORD C;
public:
	static void setscore(int num);
	Entity();
	~Entity();
	void spawnEntity(int x, int y);

	void setHP(int h);
	void setMP(int m);
	void setX(SHORT x);
	void setY(SHORT y);
	void setdirection(int direction);

	int getHP(void);
	int getMP(void);
	int getdirection(void);
	char gettype(void);
	SHORT X(void);
	SHORT Y(void);
	COORD getXY(void);
	int getID(void);
	void addtomap(char add, maps& Gamemap);
	virtual char move(double time, char ent, maps& Gamemap, COORD Player);
	char collisioncheck(maps& gamemap);
};



