#pragma once
#include"ship.h"
class AviationBattleship :public Ship
{
public:
	AviationBattleship()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AviationBattleship), 5, 5, 4, 0);
	}
	~AviationBattleship()
	{

	}

private:

};