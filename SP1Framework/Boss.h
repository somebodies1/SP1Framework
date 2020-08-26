#pragma once
#include <fstream>
#include "Entity.h"
class Boss : public Entity
{
private:
	int sprite;
	int phase;
public:
	Boss();
	~Boss();
	void setsprite(int num);
	int getsprite();
	void setphase(int num);
	int getphase();
	void printboss(maps& gamemap);
	void removeboss(maps& gamemap);
	void moveboss(int steps, maps& gamemap);
};

