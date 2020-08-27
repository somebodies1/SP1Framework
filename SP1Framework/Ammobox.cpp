#include "Ammobox.h"

Ammobox::Ammobox()
{
	hp = 2;
	type = '%';
}

Ammobox::~Ammobox()
{

}

char Ammobox::move(double time, char ent, maps& gamemap, COORD Player)
{
	gamemap.setchar(ent, C.X, C.Y);
	return 0;
}