#include "maps.h"

maps::maps()
{
    mapno = 0;
    stageno = 0;
    setcurrent(mapno);
    setstage(stageno);
}

maps::~maps()
{
}

void maps::setinitial(int mapnum)
{
    string filename;
    string line;
    switch (stageno)
    {
    case 0:
    {
        switch (mapnum)
        {
        case 0:
        {
            filename = "Stage0_1.txt";
            break;
        }
        case 1:
        {
            filename = "Stage0_2.txt";
            break;
        }
        case 2:
        {
            filename = "Stage0_3.txt";
            break;
        }
        }
        break;
    }
    case 1:
    {
        switch (mapnum)
        {
        case 0:
        {
            filename = "Stage1_1.txt";
            break;
        }
        case 1:
        {
            filename = "Stage1_2.txt";
            break;
        }
        case 2:
        {
            filename = "Stage1_3.txt";
            break;
        }
        }
        break;
    }
    case 2:
    {
        switch (mapnum)
        {
        case 0:
        {
            filename = "Stage2_1.txt";
            break;
        }
        case 1:
        {
            filename = "Stage2_2.txt";
            break;
        }
        case 2:
        {
            filename = "Stage2_3.txt";
            break;
        }
        }
        break;
    }
    case 3:
    {
        switch (mapnum)
        {
        case 0:
        {
            filename = "Stage3_1.txt";
            break;
        }
        case 1:
        {
            filename = "Stage3_2.txt";
            break;
        }
        case 2:
        {
            filename = "Stage3_3.txt";
            break;
        }
        }
        break;
    }
    case 4:
    {
        switch (mapnum)
        {
        case 0:
        {
            filename = "Stage4_1.txt";
            break;
        }
        case 1:
        {
            filename = "Stage4_2.txt";
            break;
        }
        case 2:
        {
            filename = "Stage4_3.txt";
            break;
        }
        }
        break;
    }
    case 5:
    {
        switch (mapnum)
        {
        case 0:
        {
            filename = "Stage5_1.txt";
            break;
        }
        case 1:
        {
            filename = "Stage5_2.txt";
            break;
        }
        case 2:
        {
            filename = "Stage5_3.txt";
            break;
        }
        case 3:
            filename = "Stage5_4.txt";
            break;
        }
        break;
    }
    }

    ifstream mapfile(filename);
    for (int i = 0; i < 25; i++)
    {
        getline(mapfile, line); //Gets a line from the text file
        char linearray[100]; //An array of chars
        strcpy(linearray, line.c_str()); //Turns the line of string from the text file into an array fo char
        for (int j = 0; j < 80; j++)
        {
            current[i][j] = linearray[j];
            stage[mapno][i][j] = current[i][j]; //set the map to the temp map which holds the changes to the maps (enemy positions and such)
        }
    }
}

void maps::setcurrent(int mapnum)
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            if (current[i][j] != '-') // bullets are not saved when a new map is loaded
            {
                current[i][j] = stage[mapno][i][j];
            }
        }
    }
}

void maps::setstage(int stagenum)
{
    stageno = stagenum;
    mapno = 0;
}

void maps::reset()
{
    setinitial(0);
    setstage(0);
    setstage(+1);
}

char maps::getchar(int y, int x)
{
    return current[y][x];
}

void maps::setchar(char add, int x, int y)
{
    current[y][x] = add;
    if (mapno == 0)
    {
        stage[0][y][x] = current[y][x]; //save current state of the stage
    }
    else if (mapno == 1)
    {
        stage[1][y][x] = current[y][x];
    }
    else if (mapno == 2)
    {
        stage[2][y][x] = current[y][x];
    }
    else if (mapno == 3)
    {
        stage[3][y][x] = current[y][x];
    }
    else if (mapno == 4)
    {
        stage[4][y][x] = current[y][x];
    }
    else if (mapno == 5)
    {
        stage[5][y][x] = current[y][x];
    }
}

int maps::getmapno()
{
    return mapno;
}

int maps::getstageno()
{
    return stageno;
}

void maps::setmapno(int mapnum)
{
    mapno = mapnum;
}


