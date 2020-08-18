#include "bullet.h"

bullet::bullet()
{
	x = 0;
	y = 0;
	damage = 0;
	active = false;
}

bullet::~bullet()
{
	//Blank intentionally
}

void bullet::spawn_bullet(int x, int y, int dmg, bool active)
{
	this->x = x;
	this->y = y;
	this->damage = dmg;
	this->active = active;
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
	this->damage = dmg;
}

void bullet::set_active(bool active)
{
	this->active = active;
}

int bullet::get_x(void)
{
	return this->x;
}

int bullet::get_y(void)
{
	return this->y;
}

int bullet::get_damage(void)
{
	return this->damage;
}

bool bullet::get_active(void)
{
	return this->active;
}