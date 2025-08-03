#include"ship_factory.h"
#include<iostream>

ShipFactory* ShipFactory::ship_factory = nullptr;

Ship* ShipFactory::creat_ship(ShipType type,Board* board)
{
	if (board == nullptr)
		return nullptr;

	Ship* new_ship = new Ship;

	switch (type)
	{
	case ShipType::Destroyer:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_1), ship_pos, board,2,3,0,0);
		update_pos();
		break;
	case ShipType::LightCruiser:
		new_ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_2), ship_pos, board, 3, 2, 0,0);
		update_pos();
		break;
	case ShipType::HeavyCruiser:
		break;
	case ShipType::SuperCruiser:
		break;
	case ShipType::BattleCruiser:
		break;
	case ShipType::Battleship:
		break;
	case ShipType::AviationBattleship:
		break;
	case ShipType::AircraftCarrier:
		break;
	case ShipType::LightCarrier:
		break;
	case ShipType::Submarine:
		break;
	case ShipType::RepairShip:
		break;
	default:
		break;
	}

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

