#include"ship_factory.h"
#include<iostream>

ShipFactory* ShipFactory::ship_factory = nullptr;

Ship* ShipFactory::creat_ship(ShipType type,Board* board)
{
	if (board == nullptr)
		return nullptr;

	Ship* new_ship = nullptr;

	switch (type)
	{
	case ShipType::Destroyer:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Destroyer), ship_pos, board,
			2, 2, 0, 0);
		break;
	case ShipType::LightCruiser:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_LightCruiser), ship_pos, board,
			3, 2, 1,0);
		break;
	case ShipType::HeavyCruiser:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_HeavyCruiser), ship_pos, board,
			3, 3, 1, 0);
		break;
	case ShipType::SuperCruiser:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_SuperCruiser), ship_pos, board,
			3, 3, 3, 1,SkillType::Attack_3L, 1);
		break;
	case ShipType::BattleCruiser:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_BattleCruiser), ship_pos, board,
			4, 4, 3, 1,SkillType::Attack_3L,1);
		break;
	case ShipType::Battleship:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Battleship), ship_pos, board,
			4, 4, 4, 2, SkillType::Attack_5L,1);
		break;
	case ShipType::AviationBattleship:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AviationBattleship), ship_pos, board,
			5, 5, 4, 0,SkillType::Attack_5C,1, SkillType::Detect_3x3,2);
		break;
	case ShipType::AircraftCarrier:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AircraftCarrier), ship_pos, board,
			5, 5, 3, 0,SkillType::Attack_3x3,1,SkillType::Detect_13C,3);
		break;
	case ShipType::LightCarrier:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_LightCarrier), ship_pos, board,
			5, 4, 2, 0, SkillType::Attack_5C,1, SkillType::Detect_3x3,3);
		break;
	case ShipType::Submarine:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Submarine), ship_pos, board, 
			3, 3, 1, 0,SkillType::Invisible);
		break;
	case ShipType::RepairShip:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_RepairShip), ship_pos, board, 
			3, 3, 0, 0,SkillType::Repair,7);
		break;
	default:
		break;
	}
	update_pos();
	return new_ship;
}

void ShipFactory::update_pos()
{
	if (ship_pos.y < 300)
	{
		ship_pos.y = ship_pos.y + 40;
	}
	else
	{
		ship_pos.x = ship_pos.x + 170;
		ship_pos.y = 80;
	}
}

void ShipFactory::reset_pos()
{
	ship_pos = { 660,80 };
}

