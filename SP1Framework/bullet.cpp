#include "bullet.h"

static int max_bullet = 5;

bullet::bullet()
{
	x = 0;
	y = 0;
	damage = 0;
}

bullet::~bullet()
{
	//Blank intentionally
}

void bullet::spawn_bullet(int x, int y, int dmg)
{
	this->x = x;
	this->y = y;
	damage = dmg;
}

void bullet::set_x(int x)
{
	this->x = x;
}

void bullet::set_y(int y)
{
	this->y = y;
}

void bullet::set_damage(int dmg)
{
	damage = dmg;
}

int bullet::get_damage(void)
{
	return damage;
}