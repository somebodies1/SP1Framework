#pragma once
class Entity
{
private:
	static int enemyTotal;
	int count;
	int hp, mp;
public:
	Entity();
	~Entity();

	void setHP(int h);
	void setMP(int m);

	int getHP(void);
	int getMP(void);
};

