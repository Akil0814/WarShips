#pragma once
#include"ship.h"
class Battleship :public Ship
{
public:
	Battleship()
	{
		Ship::init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Battleship), 4, 4, 4, 2, SkillType::Attack_5C,2);
	}
	~Battleship()	{	}

private:

};