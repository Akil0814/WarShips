#pragma once
#include<SDL.h>
#include"ship.h"
#include"ship_type.h"
#include"board.h"

class Board;

class ShipFactory
{
public:
	static ShipFactory* instance()//ʵ�ֵ���ģʽ
	{
		if (!ship_factory)
			ship_factory = new ShipFactory();//�̲߳���ȫ

		return ship_factory;
	}

	Ship* creat_ship(ShipType type,Board* player_board);
	void update_pos();


private:

	static ShipFactory* ship_factory;

	SDL_Point ship_pos = { 660,80 };
};