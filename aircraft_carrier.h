#pragma once
#include"ship.h"
class AircraftCarrier :public Ship
{
public:
	AircraftCarrier()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AircraftCarrier), 5, 5, 3, 0);
	}
	~AircraftCarrier()
	{

	}

private:

};