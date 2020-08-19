#pragma once
#include "Framework\timer.h"
#include "Framework\console.h"

class player
{
private:
	int hp, mp, ammo;
	COORD m_cLocation;
	bool  m_bActive;
public:
	player();
	player(int iX, int iY);
	~player();
	void spawn_player(int h, int m, int a);
	void set_hp(int h);
	void set_mp(int m);
	void set_ammo(int a);

	int get_hp(void);
	int get_mp(void);
	int get_ammo(void);
	void moveCharacter(Console g_console, char Gamemap[80][25], int direction);


};

