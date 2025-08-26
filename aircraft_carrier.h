#pragma once
#include"ship.h"
class AircraftCarrier :public Ship
{
public:
	AircraftCarrier()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AircraftCarrier), 5, 5, 4, 0, SkillType::Detect_13C,2);
	}
	~AircraftCarrier(){}

private:

};