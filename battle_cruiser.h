#pragma once
#include"ship.h"
class BattleCruiser :public Ship
{
public:
	BattleCruiser()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_BattleCruiser), 4, 4, 2, 1, SkillType::Attack_5C,1);
	}
	~BattleCruiser(){}

private:

};