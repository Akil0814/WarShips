#pragma once
#include"ship.h"
class Destroyer:public Ship
{
public:
	Destroyer()
	{
		Ship::init_ship();
	}
	~Destroyer();

private:

};