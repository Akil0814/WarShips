#include"ship_factory.h"

ShipFactory* ShipFactory::ship_factory = nullptr;

Ship* ShipFactory::creat_ship(ShipType type)
{
	Ship* new_ship = new Ship;

	switch (type)
	{
	case ShipType::Destroyer:
		break;
	case ShipType::LightCruiser:
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
