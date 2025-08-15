#pragma once
#include"ship.h"
class Submarine :public Ship
{
public:
	Submarine()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Submarine), 3, 3, 1, 0);
	}
	~Submarine()
	{

	}

private:

};