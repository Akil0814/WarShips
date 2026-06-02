#pragma once
#include<SDL.h>
#include"ship.h"
#include"ship_type.h"

#include"destroyer.h"
#include"light_cruiser.h"
#include"heavy_cruiser.h"
#include"super_cruiser.h"
#include"battle_cruiser.h"
#include"battleship.h"
#include"aviation_battleship.h"
#include"aircraft_carrier.h"
#include"light_carrier.h"
#include"submarine.h"
#include"repair_ship.h"


#include"board.h"

class Board;

class ShipFactory
{
public:
	static ShipFactory* instance()//实现单例模式
	{
		if (!ship_factory)
			ship_factory = new ShipFactory();//线程不安全

		return ship_factory;
	}

	Ship* creat_ship(ShipType type,Board* player_board);

	void update_pos();
	void reset_pos();

private:
	ShipFactory() = default;

private:

	static ShipFactory* ship_factory;

	SDL_Point ship_pos = { 660,80 };
};