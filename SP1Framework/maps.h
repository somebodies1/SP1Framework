#pragma once
#include <fstream>
#include <string>
using namespace std;
class maps
{
private:
	char stage0[3][25][80];
	char stage1[3][25][80];
	char stage2[3][25][80];
	char stage[10][25][80]; //currently allows each stage to have 10 maps max
	char current[25][80];
	int mapno;
	int stageno;
public:
	maps();
	~maps();
	void setinitial(int mapnum); //set the initial map by reading from text file
	void setcurrent(int mapnum);
	void setstage(int stagenum);
	char getchar(int y, int x); //Gets the character in the index
	void setchar(char add, int x, int y); //Sets the character in the index
	int getmapno();
	int getstageno();
	void setmapno(int mapnum);
	void reset();
};

