#pragma once
#include"ship.h"
class Destroyer:public Ship
{
public:
	Destroyer()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Destroyer),2, 2, 0, 0);
	}
	~Destroyer()
	{

	}

private:

};