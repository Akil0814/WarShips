#pragma once
#include"ship.h"
class HeavyCruiser :public Ship
{
public:
	HeavyCruiser()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_HeavyCruiser), 3, 3, 1, 0);
	}
	~HeavyCruiser()
	{

	}

private:

};