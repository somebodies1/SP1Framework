#include "player.h"


player::player()
{
	hp = 3;
	mp = 5;
	ammo = 10;
    m_cLocation.X = 2;
    m_cLocation.Y = 22;
    m_bActive = true;
}

player::player(int iX, int iY)
{
    hp = 1;
    mp = 1;
    ammo = 1;
    m_cLocation.X = iX;
    m_cLocation.Y = iY;
    m_bActive = true;
}
player::~player()
{
	//blank intentionally
}

void player::spawn_player(int h, int m, int a)
{
	hp = h;
	mp = m;
	ammo = a;
}

void player::set_hp(int h)
{
	hp = h;
}

void player::set_mp(int m)
{
	mp = m;
}

void player::set_ammo(int a)
{
	ammo = a;
}

int player::get_hp(void)
{
	return hp;
}

int player::get_mp(void)
{
	return mp;
}

int player::get_ammo(void)
{
	return ammo;
}

void player::moveCharacter()
{

}


