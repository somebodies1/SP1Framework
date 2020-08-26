#pragma once
#include <fstream>
#include "Entity.h"
class Boss : public Entity
{
private:
	int sprite;
	static char sprite1[3][10];
public:
	Boss();
	~Boss();
	void setsprite(int num);
	int getsprite();
	void printboss(maps& gamemap);
	void removeboss(maps& gamemap);
	void moveboss(int direction, int steps, maps& gamemap);
};

