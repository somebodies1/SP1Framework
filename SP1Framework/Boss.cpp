#include "Boss.h"

Boss::Boss()
{
	hp = 40;
    Phase = 1;
    C.X = 4;
    C.Y = 4;
}

Boss::~Boss()
{

}

void Boss::printboss(maps& gamemap)
{
    string line;
    ifstream bossfile("BossSprite.txt");
    for (int i = 0; i < 3; i++)
    {
        getline(bossfile, line); //Gets a line from the text file
        char linearray[100]; //An array of chars
        strcpy(linearray, line.c_str()); //Turns the line of string from the text file into an array fo char
        for (int j = 0; j < 10; j++)
        {           
            gamemap.setchar(linearray[j],C.X+j, C.Y+i);
        }
    }
}

void Boss::removeboss(maps& gamemap)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gamemap.setchar(' ', C.X+j, C.Y+i);
        }
    }
}

void Boss::moveboss(int direction, int steps, maps& gamemap)
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
