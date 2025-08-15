#pragma once
#include"ship.h"
class RepairShip :public Ship
{
public:
	RepairShip()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_RepairShip), 3, 3, 0, 0);
	}
	~RepairShip()
	{

	}

private:

};