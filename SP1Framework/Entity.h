#pragma once
class Entity
{
private:
	static int enemyTotal;
	static int count;
	int hp, mp;
public:
	Entity();
	~Entity();
	void spawnEntity(int h, int m);
	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};

class Entity
{
};

