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
	void set_hp(int h);
	void set_mp(int m);
	void set_ammo(int a);
	int get_hp(void);
	int get_mp(void);
	int get_ammo(void);
	bool moveplayer(maps &gamemap, int direction);



};

