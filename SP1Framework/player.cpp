#include "player.h"


player::player()
{
	hp = 3;
	mp = 5;
	ammo = 10;
    C.X = 1;
    C.Y = 22;
    m_bActive = true;
}

player::player(int iX, int iY)
{
    hp = 1;
    mp = 1;
    ammo = 1;
    C.X = iX;
    C.Y = iY;
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

void player::set_ammo(int a)
{
	ammo = a;
}

int player::get_ammo(void)
{
	return ammo;
}

bool player::moveplayer( maps &Gamemap, maps &Entitylayer, int direction)
{
    int iX = C.X;
    int iY = C.Y;
    if (direction == 1)
    {
        if (Gamemap.getchar(iY,iX) == 'H' && Gamemap.getchar(iY-1,iX) != '=' || Gamemap.getchar(iY - 1, iX) == 'H')
        {
            C.Y--;
        }
    }
    if (direction == 2)
    {
        if (Gamemap.getchar(iY,iX - 1) == ' ' || Gamemap.getchar(iY,iX - 1) == 'H')
        {
            C.X--;
            if (player::fireright != false)
            {
                player::fireright = false;
            }
        }
        else if (Gamemap.getchar(iY,iX - 1) == '+')
        {
            Gamemap.setmapno(Gamemap.getmapno() - 1);
            Gamemap.setcurrent(Gamemap.getmapno());
            Entitylayer.setmapno(Entitylayer.getmapno() - 1);
            Entitylayer.setcurrent(Entitylayer.getmapno());
            C.X =+ 78;
            return true;
        }
    }
    if (direction == 3)
    {
        if (Gamemap.getchar(iY,iX) == 'H' && Gamemap.getchar(iY+1,iX) != '=' || Gamemap.getchar(iY + 1, iX) == 'H')
       {
            C.Y++;
        }
    }
    if (direction == 4)
    {
        if (Gamemap.getchar(iY,iX + 1) == ' ' || Gamemap.getchar(iY,iX + 1) == 'H')
        {
            C.X++;
            if (player::fireright != true)
            {
                player::fireright = true;
            }

        }
        else if (Gamemap.getchar(iY,iX + 1) == '+')
        {
            Gamemap.setmapno(Gamemap.getmapno() + 1);
            Gamemap.setcurrent(Gamemap.getmapno());
            Entitylayer.setmapno(Entitylayer.getmapno() + 1);
            Entitylayer.setcurrent(Entitylayer.getmapno());
            C.X -= 77;
            return true;
        }
    }
    if (Gamemap.getchar(iY + 1,iX) == ' ' && Gamemap.getchar(iY, iX) != 'H')
    {
        C.Y++;
    }
    return false;
}




