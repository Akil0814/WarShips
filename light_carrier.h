#pragma once
#include"ship.h"
class LightCarrier :public Ship
{
public:
	LightCarrier()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_LightCarrier), 5, 4, 3, 0, SkillType::Detect_3x3, 2);
	}
	~LightCarrier(){	}

private:

};