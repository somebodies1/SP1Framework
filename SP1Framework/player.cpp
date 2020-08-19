#include "player.h"
#include "game.h"


player::player()
{
	hp = 1;
	mp = 1;
	ammo = 1;
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

    if (level1 == true)
    {
        int iX = g_sChar.m_cLocation.X;
        int iY = g_sChar.m_cLocation.Y;

        if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 0)
        {
            //Beep(1440, 100);
            if (Gamemap[iY][iX] == 'H' && Gamemap[iY - 1][iX] == 'H')
            {
                g_sChar.m_cLocation.Y--;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 0)
        {
            //Beep(2000, 30);
            if (Gamemap[iY][iX - 1] == ' ' || Gamemap[iY][iX - 1] == 'H')
            {
                g_sChar.m_cLocation.X--;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
        {
            //Beep(2440, 30);
            if (Gamemap[iY][iX] == 'H' && Gamemap[iY + 1][iX] == 'H') //For moving up and down the ladder
            {
                g_sChar.m_cLocation.Y++;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_RIGHT].keyDown && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
        {
            //Beep(1000, 30);
            if (Gamemap[iY][iX + 1] == ' ' || Gamemap[iY][iX + 1] == 'H')
            {
                g_sChar.m_cLocation.X++;
            }
            else if (Gamemap[iY][iX + 1] == '+')
            {
                level1 = false;
                level2 = true;
                g_sChar.m_cLocation.X = 1;
                g_sChar.m_cLocation.Y = 22;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_SPACE].keyDown)
        {
            Beep(1000, 30);
            Beep(500, 50);
            Beep(1500, 20);
            g_sChar.m_bActive = !g_sChar.m_bActive;
        }
    }
    else if (level2 == true)
    {
        // Updating the location of the character based on the key release
        // providing a beep sound whenver we shift the character
        int iX = g_sChar.m_cLocation.X;
        int iY = g_sChar.m_cLocation.Y;

        //g_sChar.m_cLocation.X = 1;
        //g_sChar.m_cLocation.Y = 22;


        if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 0)
        {
            //Beep(1440, 100);
            if (Gamemap1[iY][iX] == 'H' && Gamemap1[iY - 1][iX] == 'H')
            {
                g_sChar.m_cLocation.Y--;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 0)
        {
            //Beep(2000, 30);
            if (Gamemap1[iY][iX - 1] == ' ' || Gamemap1[iY][iX - 1] == 'H')
            {
                g_sChar.m_cLocation.X--;
            }
            else if (Gamemap1[iY][iX - 1] == '+')
            {
                level2 = false;
                level1 = true;
                g_sChar.m_cLocation.X = 78;
                g_sChar.m_cLocation.Y = 22;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
        {
            //Beep(2440, 30);
            if (Gamemap1[iY][iX] == 'H' && Gamemap1[iY + 1][iX] == 'H') //For moving up and down the ladder
            {
                g_sChar.m_cLocation.Y++;
            }
            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_RIGHT].keyDown && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
        {
            //Beep(1000, 30);
            if (Gamemap1[iY][iX + 1] == ' ' || Gamemap1[iY][iX + 1] == 'H')
            {
                g_sChar.m_cLocation.X++;
            }

            else
            {
                Beep(2000, 100);
            }
        }
        if (g_skKeyEvent[K_SPACE].keyDown)
        {
            Beep(1000, 30);
            Beep(500, 50);
            Beep(1500, 20);
            g_sChar.m_bActive = !g_sChar.m_bActive;
        }
    }
}

