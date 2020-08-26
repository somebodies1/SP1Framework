#include "Boss.h"

Boss::Boss()
{
	hp = 30;
    sprite = 1;
    phase = 1;
    C.X = 64;
    C.Y = 20;
}

Boss::~Boss()
{
    mp += 300;
}

void Boss::setsprite(int num)
{
    while (num > 5)
    {
        num -= 5;
    }
    sprite = num;
}

int Boss::getsprite()
{
    return sprite;
}

void Boss::setphase(int num)
{
    phase = num;
}

int Boss::getphase()
{
    return phase;
}

void Boss::printboss(maps& gamemap)
{
    int spritenum = 0;
    int start = 0;
    int stop = 0;
    string line;
    ifstream bossfile("BossSprite.txt");
    if (sprite == 1)
    {
        start = 0;
        stop = 8;
    }
    else if (sprite == 2)
    {
        start = 9;
        stop = 17;
    }
    else if (sprite == 3)
    {
        start = 18;
        stop = 26;
    }
    else if (sprite == 4)
    {
        start = 27;
        stop = 35;
    }
    else if (sprite == 5)
    {
        start = 36;
        stop = 44;
    }
    for (int i = 0; i < 3; i++)
    {
        getline(bossfile, line); //Gets a line from the text file
        char linearray[100]; //An array of chars
        strcpy(linearray, line.c_str()); //Turns the line of string from the text file into an array fo cha
        for (int j = 0; j < 48; j++)
        {
            if (j >= start && j <= stop)
            {
                gamemap.setchar(linearray[j], C.X + j - start, C.Y + i);
            }
        }
    }
}

void Boss::removeboss(maps& gamemap)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            gamemap.setchar(' ', C.X + j, C.Y + i);
        }
    }
}

void Boss::moveboss(int steps, maps& gamemap)
{
    removeboss(gamemap);
    switch (direction)
    {
    case 1:C.Y = C.Y - steps; //1^ 2> 3< 4v
        break;
    case 2:C.X = C.X - steps;
        break;
    case 3:C.Y = C.Y + steps;
        break;
    case 4:C.X = C.X + steps;
        break;
    }
    printboss(gamemap);
}
