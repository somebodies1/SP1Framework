#pragma once
#include "Framework\timer.h"
#include "Framework\console.h"
#include "maps.h"
#include "Entity.h"
#include "bullet.h"

class player: public Entity
{
private:
	int ammo;
	bool  m_bActive;
public:
	player();
	player(int iX, int iY);
	~player();
	void set_ammo(int a);
	int get_ammo(void);
	char moveplayer(maps &gamemap, maps &entitylayer, int direction);  // The 2 layer are entered as passby parameters to updated 
	bool fireright = true;
	void minusammo();
};

