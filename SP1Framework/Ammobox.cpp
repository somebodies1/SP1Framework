#include "Ammobox.h"

Ammobox::Ammobox()
{
	hp = 2;
	type = '%';
}

Ammobox::~Ammobox()
{
	score += 10;
}

char Ammobox::move(double time, char ent, maps& gamemap, COORD Player)
{
	gamemap.setchar(ent, C.X, C.Y);
	return 0;
}