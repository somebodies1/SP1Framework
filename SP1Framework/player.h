#pragma once
class player
{
private:
	int hp, mp, ammo;
public:
	player();
	~player();
	void spawn_player(int h, int m, int a);

	void set_hp(int h);
	void set_mp(int m);
	void set_ammo(int a);

	int get_hp(void);
	int get_mp(void);
	int get_ammo(void);
};

