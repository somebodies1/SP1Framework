#pragma once
class bullet
{
private:
	int damage;
	int x, y;
	bool active;
public:
	bullet();
	~bullet();

	void spawn_bullet(int x, int y, int dmg, bool active);

	//setters
	void set_x(int x);
	void set_y(int y);
	void set_damage(int dmg);
	void set_active(bool active);

	//getters
	int get_x(void);
	int get_y(void);
	int get_damage(void);
	bool get_active(void);
};

