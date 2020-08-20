#pragma once
class maps
{
private:
	static char stage1_1[25][80];
	static char stage1_2[25][80];
	static char stage1_3[25][80];
	static char tut_1[25][80];
	static char tut_2[25][80];
	static char tut_3[25][80];
	char current[25][80];
	int mapno;
public:
	maps();
	~maps();
	void setcurrent(int mapnum);
	char getchar(int x, int y); //Gets the character in the index
	void setchar(char add, int x, int y); //Sets the character in the index
	int getmapno();
	void setmapno(int mapnum);
};

