#include "player.h"


player::player()
{
	hp = 3;
	mp = 5;
	ammo = 10;
    m_cLocation.X = 1;
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

COORD player::getcoord(void)
{
    return m_cLocation;
}

void player::moveplayer( maps &Gamemap, int direction)
{
    int iX = m_cLocation.X;
    int iY = m_cLocation.Y;
    if (direction == 1)
    {
        //Beep(1440, 100);
        if (Gamemap.getchar(iY,iX) == 'H' && Gamemap.getchar(iY-1,iX) == 'H')
        {
            m_cLocation.Y--;
        }
        else
        {
            Beep(3000, 200);
        }
    }
    if (direction == 2)
    {
        //Beep(2000, 30);
        if (Gamemap.getchar(iY,iX - 1) == ' ' || Gamemap.getchar(iY,iX - 1) == 'H')
        {
            m_cLocation.X--;
        }
        else if (Gamemap.getchar(iY,iX - 1) == '+')
        {
            Gamemap.setcurrent(0);
            m_cLocation.X =+ 78;
        }
        else
        {
            Beep(3000, 200);
        }
    }
    if (direction == 3)
    {
        //Beep(2440, 30);
        if (Gamemap.getchar(iY,iX) == 'H' && Gamemap.getchar(iY+1,iX) == 'H') //For moving up and down the ladder
        {
            m_cLocation.Y++;
        }
        else
        {
            Beep(3000, 200);
        }
    }
    if (direction == 4)
    {
        //Beep(1000, 30);
        if (Gamemap.getchar(iY,iX + 1) == ' ' || Gamemap.getchar(iY,iX + 1) == 'H')
        {
            m_cLocation.X++;
        }
        else if (Gamemap.getchar(iY,iX + 1) == '+')
        {
            Gamemap.setcurrent(1);
            m_cLocation.X -= 77;
        }
        else
        {
            Beep(3000, 200);
        }
    }
    if (Gamemap.getchar(iY + 1,iX) == ' ')
    {
        m_cLocation.Y++;
    }
}


