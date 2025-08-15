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
		new_ship=new Destroyer;

		break;
	case ShipType::LightCruiser:
		new_ship = new LightCruiser;

		break;
	case ShipType::HeavyCruiser:
		new_ship = new HeavyCruiser;

		break;
	case ShipType::SuperCruiser:
		new_ship = new SuperCruiser;

		break;
	case ShipType::BattleCruiser:
		new_ship = new BattleCruiser;

		break;
	case ShipType::Battleship:
		new_ship = new Battleship;

		break;
	case ShipType::AviationBattleship:
		new_ship = new AviationBattleship;

		break;
	case ShipType::AircraftCarrier:
		new_ship = new AircraftCarrier;

		break;
	case ShipType::LightCarrier:
		new_ship = new LightCarrier;

		break;
	case ShipType::Submarine:
		new_ship = new Submarine;

		break;
	case ShipType::RepairShip:
		new_ship = new RepairShip;

		break;
	default:
		break;
	}

	new_ship->set_position(ship_pos);
	new_ship->set_board_in(board);
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

