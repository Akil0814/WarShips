#include"ship.h"
#include<iostream>

void Ship::init_ship(SDL_Texture* texture, SDL_Point first_pos, Board* board,
					int size, int hp, int atk_time, int defense_time, SkillType skill)
{

	ship_texture = texture;
	set_position(first_pos);
	last_position = first_pos;
	player_board = board;

	ship_size = size;
	render_rect.h = SIZE_TILE, render_rect.w = SIZE_TILE * size;

	this->hp = hp;
	this->atk_time = atk_time;
	this->defense_time = defense_time;

	if (!(skill == SkillType::NONE))
	{
		this->ship_skill = skill;
		have_skill = true;
	}
}

void Ship::on_update(double delta)
{
	
}

void Ship::on_render(SDL_Renderer* renderer)
{
	static SDL_Point pivot{ SIZE_TILE/2, SIZE_TILE/2 };//Ðý×ªÖÐÐÄ
	if (horizontal)
		SDL_RenderCopyEx(renderer, ship_texture, nullptr, &render_rect, 0, &pivot, SDL_FLIP_NONE);
	else
		SDL_RenderCopyEx(renderer, ship_texture, nullptr, &render_rect, 90.0, &pivot, SDL_FLIP_NONE);
}

void Ship::on_input(const SDL_Event& event)
{

	if (event.type == SDL_MOUSEBUTTONDOWN && check_cursor_hit(event.button.x, event.button.y))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			ship_in_move = true;
			delta.x = event.button.x - collision_rect.x;
			delta.y = event.button.y - collision_rect.y;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			if (!ship_in_move&&ship_in_board)
			{
				ship_rotate = true;
				rotate_ship();
			}
		}
		std::cout << "in if 1" << std::endl;
	}

	if (ship_in_move && event.type == SDL_MOUSEMOTION)
	{
		set_position({ event.motion.x - delta.x, event.motion.y - delta.y });
		std::cout << "in if 2" << std::endl;

	}

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		ship_in_move = false;
		delta = {0};

		if (player_board->is_inside(event.button.x, event.button.y))
		{
			if (player_board->place_ship(this, { event.button.x,event.button.y }, ship_size, horizontal))
			{
				set_position(absolute_position);
				ship_in_board;
			}
			else
				set_position(last_position);
		}
		std::cout << "in if 3" << std::endl;

	}

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT)
	{
		if (ship_rotate)
		{
			ship_rotate = false;
		}
		std::cout << "in if 4" << std::endl;

	}

}

void Ship::rotate_ship()
{
	horizontal = !horizontal;
	
	update_rect();
}

void Ship::update_rect()
{
	collision_rect.x = absolute_position.x;
	collision_rect.y = absolute_position.y;
	render_rect.x = absolute_position.x;
	render_rect.y = absolute_position.y;
	if (horizontal) {
		collision_rect.w = SIZE_TILE * ship_size;
		collision_rect.h = SIZE_TILE;
	}
	else {
		collision_rect.w = SIZE_TILE;
		collision_rect.h = SIZE_TILE * ship_size;
	}
}

void Ship::set_position(const SDL_Point& pos)
{
	absolute_position = pos;

	update_rect();
}

const SDL_Point& Ship::get_position()const
{
	return absolute_position;
}

bool Ship::check_cursor_hit(int x, int y)const
{
	return x >= collision_rect.x && x < (collision_rect.x + collision_rect.w) &&
		y >= collision_rect.y && y < (collision_rect.y + collision_rect.h);
}