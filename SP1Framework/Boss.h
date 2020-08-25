#pragma once
#include <fstream>
#include "Entity.h"
class Boss : public Entity
{
private:
	int Phase;
	static char sprite1[3][10];
public:
	Boss();
	~Boss();
	void printboss(maps& gamemap);
	void removeboss(maps& gamemap);
	void moveboss(int direction, int steps, maps& gamemap);
};

