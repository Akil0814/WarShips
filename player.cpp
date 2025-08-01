#include"player.h"

#include<iostream>

Player::Player()
{
	board.set_board_pos({30, 30});
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

