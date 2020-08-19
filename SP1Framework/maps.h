#pragma once
class maps
{
private:
	static char gamemap[25][80];
	static char gamemap1[25][80];
	char current[25][80];
	int mapno;
public:
	maps();
	~maps();
	void setcurrent(int mapnum);
	char getchar(int x, int y);
	int getmapno();
	void setmapno(int mapnum);
};

