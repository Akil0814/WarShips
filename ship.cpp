#include"ship.h"
#include<iostream>

void Ship::init_ship(SDL_Texture* texture, SDL_Point first_pos, Board* board,
					int size, int hp, int atk_time, int defense_time, SkillType skill1,int time_1, SkillType skill2,int time_2)
{

	ship_texture = texture;
	last_position = first_pos;
	player_board = board;

	ship_size = size;
	render_rect.h = SIZE_TILE, render_rect.w = SIZE_TILE * size;
	set_position(first_pos);


	this->hp = hp;
	this->atk_time = atk_time;
	this->defense_time = defense_time;

	this->skill_1 = skill1;
	skill1_time = time_1;
	this->skill_2 = skill2;
	skill2_time = time_2;
}

void Ship::on_update(double delta)
{
	
}

void Ship::on_render(SDL_Renderer* renderer)
{
	if (ship_in_move)
		player_board->show_place_feasibility(renderer, absolute_position, ship_size, horizontal);

	if (ship_in_rotate)
		player_board->show_place_feasibility(renderer, absolute_position, ship_size, !horizontal);

	static SDL_Point pivot{ SIZE_TILE/2, SIZE_TILE/2 };//旋转中心
	if (horizontal)
		SDL_RenderCopyEx(renderer, ship_texture, nullptr, &render_rect, 0, &pivot, SDL_FLIP_NONE);
	else
		SDL_RenderCopyEx(renderer, ship_texture, nullptr, &render_rect, 90.0, &pivot, SDL_FLIP_NONE);
}

void Ship::on_input(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && check_cursor_hit(event.button.x, event.button.y))
	{

		if (event.button.button == SDL_BUTTON_LEFT && !ship_in_rotate)//开始拖拽船只逻辑
		{
			ship_in_move = true;
			delta.x = event.button.x - collision_rect.x;
			delta.y = event.button.y - collision_rect.y;
			player_board->move_ship({ absolute_position.x,absolute_position.y }, ship_size, horizontal);
		}

		if (event.button.button == SDL_BUTTON_RIGHT && !ship_in_move && ship_in_board)//开始旋转船只逻辑
		{
			ship_in_rotate = true;
			player_board->move_ship({ absolute_position.x,absolute_position.y }, ship_size, horizontal);
		}
	}

	if (ship_in_move && event.type == SDL_MOUSEMOTION)//拖拽中
		set_position({ event.motion.x - delta.x, event.motion.y - delta.y });

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && ship_in_move)//停止拖拽
	{
		ship_in_move = false;
		delta = { 0 };

		if (player_board->is_inside(event.button.x, event.button.y))
		{
			SDL_Point new_pos = player_board->place_ship(this, { absolute_position.x,absolute_position.y }, ship_size, horizontal);
			if (new_pos.x>=0)
			{
				set_position(new_pos);
				ship_in_board=true;
				last_position = new_pos;
				Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Put_In_Water), 0);
			}
			else
			{
				player_board->place_ship(this, { last_position.x,last_position.y }, ship_size, horizontal);
				set_position(last_position);
				Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Error), 0);
			}
		}
		else
		{
			set_position(last_position);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Error), 0);
			if (ship_in_board != false)
			{
				player_board->place_ship(this, { last_position.x,last_position.y }, ship_size, horizontal);
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT && ship_in_rotate && !ship_in_move)//完成旋转逻辑
	{
		ship_in_rotate = false;
		SDL_Point new_pos = player_board->place_ship(this, { absolute_position.x,absolute_position.y }, ship_size, !horizontal);
		if (new_pos.x >= 0)
		{
			rotate_ship();
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Put_In_Water), 0);
		}
		else
		{
			player_board->place_ship(this, { last_position.x,last_position.y }, ship_size, horizontal);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Error), 0);
		}

	}

	if (event.window.event == SDL_WINDOWEVENT_LEAVE && ship_in_move)
	{
		ship_in_move = false;
		delta = { 0 };
		set_position(last_position);
		Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Error), 0);
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

bool Ship::check_cursor_hit(int x, int y)const
{
	return x >= collision_rect.x && x < (collision_rect.x + collision_rect.w) &&
		y >= collision_rect.y && y < (collision_rect.y + collision_rect.h);
}

SkillType Ship::get_skill_1()const
{
	return skill_1;
}

SkillType Ship::get_skill_2()const
{
	return skill_2;
}

bool Ship::is_in_board()const
{
	return ship_in_board;
}
 
void Ship::take_damage()
{
	if (defense_time > 0)
		defense_time--;
	else
		hp--;
	if (hp <= 0)
		sink = true;
}

bool Ship::is_sink()const
{
	return sink;
}

int Ship::get_atk_time()const
{
	return atk_time;
}

int Ship::get_skill_1_time()const
{
	return skill1_time;
}

int Ship::get_skill_2_time()const
{
	return skill2_time;
}

bool Ship::check_motion()const
{
	return ship_in_move;
}