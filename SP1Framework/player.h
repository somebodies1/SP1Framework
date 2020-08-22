#pragma once
#include "Framework\timer.h"
#include "Framework\console.h"
#include "maps.h"
#include "Entity.h"

class player: public Entity
{
private:
	int ammo;
	bool  m_bActive;
public:
	player();
	player(int iX, int iY);
	~player();
	void spawn_player(int h, int m, int a);
	void set_ammo(int a);
	int get_ammo(void);
	bool moveplayer(maps &gamemap, int direction);
	bool fireright = true;
};

