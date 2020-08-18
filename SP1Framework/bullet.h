#pragma once
class bullet
{
private:
	int damage;
	int x, y;
public:
	bullet();
	~bullet();

	void spawn_bullet(int x, int y, int dmg);
	void set_x(int x);
	void set_y(int y);
	void set_damage(int dmg);
	int get_damage(void);
};

