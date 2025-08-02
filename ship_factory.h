#pragma once
#include<SDL.h>
#include"ship.h"
#include"ship_type.h"

class ShipFactory
{
public:
	static ShipFactory* instance()//实现单例模式
	{
		if (!ship_factory)
			ship_factory = new ShipFactory();//线程不安全

		return ship_factory;
	}

	Ship* creat_ship(ShipType type);

private:

	static ShipFactory* ship_factory;

	SDL_Point ship_pos = { 0 };
};