#pragma once
#include "Entity.h"
class bullet: public Entity
{
private:
	static int bulletnumber;
	int damage;
public:
	bullet();
	bullet(int direction, int x, int y);
	~bullet();

	void spawn_bullet(int direction, int iX, int iY);
	void set_x(int x);
	void set_y(int y);
	void set_damage(int dmg);
	int get_damage(void);
	static int getbulletnumber();
	char move(char ent, maps& Gamemap); //Also doubles as a collisions detection
};

