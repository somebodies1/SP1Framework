#include "Health.h"

Health::Health()
{
	hp = 2;
	type = '+';
}

Health::~Health()
{

}

char Health::move(double time, char ent, maps& gamemap, COORD Player)
{
	gamemap.setchar(ent, C.X, C.Y);
	return 0;
}
