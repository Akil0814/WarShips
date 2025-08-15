#pragma once
#include"ship.h"
class LightCruiser :public Ship
{
public:
	LightCruiser()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_LightCruiser), 3, 2, 1, 0);
	}
	~LightCruiser()
	{

	}

private:

};