#pragma once
#include<SDL.h>
#include"ship.h"
#include"ship_type.h"

class ShipFactory
{
public:
	static ShipFactory* instance()//ʵ�ֵ���ģʽ
	{
		if (!ship_factory)
			ship_factory = new ShipFactory();//�̲߳���ȫ

		return ship_factory;
	}

	Ship* creat_ship(ShipType type);

private:

	static ShipFactory* ship_factory;

	SDL_Point ship_pos = { 0 };
};