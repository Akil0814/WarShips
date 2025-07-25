#include"player.h"

#include<iostream>//test
/*
 1.边界旋转有概率异常退回操作
*/

Player::Player()
{
	Ship* ship = new Ship;
	ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_5), 5, { 570,50 });
	ship_list.push_back(ship);

	ship = new Ship;
	ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_4), 4, { 570,120 });
	ship_list.push_back(ship);

	ship = new Ship;
	ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_3), 3, { 570,190 });
	ship_list.push_back(ship);

	ship = new Ship;
	ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_2), 3, { 570,260 });
	ship_list.push_back(ship);

	ship = new Ship;
	ship->init_ship(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_1), 2, { 570,330 });

	ship_list.push_back(ship);
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
	if (have_ship_in_move == true)
	{
		current_ship->on_input(event);
		if (!current_ship->check_motion())
		{
			have_ship_in_move = false;

			SDL_Point p = board.place_ship(current_ship->get_position(), current_ship->get_ship_size(), current_ship->is_horizontal());
			if (p.x != -1)
			{
				current_ship->set_position(p);
				std::cout << "place_ship pass" << std::endl;
			}
			else
			{
				std::cout << "place_ship fall" << std::endl;
				if (!current_ship->is_horizontal() == current_ship_last_hor_state)
				{
					current_ship->rotate_ship();
					std::cout << "rotate in motion" << std::endl;

				}
				current_ship->set_position(current_ship_last_pos);
				board.place_ship(current_ship_last_pos, current_ship->get_ship_size(), current_ship->is_horizontal());
				std::cout << "reverse" << std::endl;
			}
			current_ship = nullptr;
			std::cout << "stop move" << std::endl;
		}
	}

	else 
	{
		for (auto& ship : ship_list)
		{
			ship->on_input(event);
			if (ship->check_motion())
			{
				std::cout << "check_motion start" << std::endl;
				have_ship_in_move = true;
				current_ship = ship;
				current_ship_last_pos = current_ship->get_position();
				current_ship_last_hor_state = current_ship->is_horizontal();
				board.move_ship(current_ship_last_pos, current_ship->get_ship_size(), current_ship->is_horizontal());

			}
			if (ship->check_rotate())
			{
				current_ship = ship;
				current_ship_last_pos = current_ship->get_position();
				current_ship_last_hor_state = current_ship->is_horizontal();
				board.move_ship(current_ship_last_pos, current_ship->get_ship_size(), !current_ship->is_horizontal());

				SDL_Point p = board.place_ship(current_ship->get_position(), current_ship->get_ship_size(), current_ship->is_horizontal());
				if (p.x != -1)
				{
					current_ship->set_position(p);
					std::cout << "check_rotate pass" << std::endl;
				}
				else
				{
					current_ship->rotate_ship();
					current_ship->set_position(current_ship_last_pos);
					board.place_ship(current_ship_last_pos, current_ship->get_ship_size(), current_ship->is_horizontal());
					std::cout << "check_rotate fall" << std::endl;
				}
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

