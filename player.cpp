#include"player.h"

#include<iostream>

Player::Player()
{
	board.set_board_pos({30, 50});
}

Player::~Player()
{
	for (auto& ship : ship_list)
		delete ship;
}
					
void Player::on_render(SDL_Renderer* renderer)	//局内 
{
	board.on_render(renderer);
}

void Player::on_render(SDL_Renderer* renderer,bool setup)
{
	board.on_render(renderer);

	for (auto& ship : ship_list)
		ship->on_render(renderer);

	if (current_ship != nullptr)
		current_ship->on_render(renderer);
}


void Player::on_update(double delta)
{
	board.on_update(delta);//局内
}

void Player::on_update(double delta, bool setup)
{
	for (auto& ship : ship_list)
		ship->on_update(delta);
}


void Player::on_input(const SDL_Event& event)
{
	board.on_input(event);
}

void Player::on_input(const SDL_Event& event,bool setup)
{
	if (have_ship_in_move == true)
	{
		current_ship->on_input(event);
		if (!current_ship->check_motion())
		{
			have_ship_in_move = false;
			current_ship = nullptr;
		}
	}
	else
	{
		for (auto& ship : ship_list)
		{
			ship->on_input(event);
			if (ship->check_motion())
			{
				have_ship_in_move = true;
				current_ship = ship;
			}
		}
	}
}

void Player::set_board_pos(SDL_Point pos)
{
	board.set_board_pos(pos);
}

bool Player::finish_round()
{
	if (board.finish_hit_time())
	{
		board.reset_hit_time();
		return true;
	}
	return false;
}

void Player::draw_cover(SDL_Renderer* renderer)
{
	board.draw_cover(renderer);
}

void Player::add_ship(Ship* new_ship)
{
	if(new_ship!=nullptr)
		ship_list.push_back(new_ship);
}


bool Player::spend_coin(int cost)
{
	if (cost > coin_have)
		return false;

	coin_have -= cost;
	return true;
}

Board* Player::get_board()
{
	return &board;
}

void Player::finish_setting()
{
	auto it = std::remove_if(ship_list.begin(), ship_list.end(),
		[](auto& e) { return !e->is_in_board(); });
	ship_list.erase(it, ship_list.end());
}

void Player::reset()
{
	board.reset_board();
	coin_have = 210;
	have_ship_in_move = false;
	current_ship = nullptr;

	for (auto iter : ship_list)
	{
		delete iter;
	}
	ship_list.clear();
}

int Player::get_coin()
{
	return coin_have;
}




