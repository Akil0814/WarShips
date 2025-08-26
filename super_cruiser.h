#pragma once
#include"ship.h"
class SuperCruiser :public Ship
{
public:
	SuperCruiser()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_SuperCruiser), 3, 3, 2, 1,SkillType::Attack_3x3,1);
	}
	~SuperCruiser(){}

private:

};