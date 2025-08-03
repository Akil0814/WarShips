#pragma once
#include<SDL.h>
#include"board.h"
#include"tile.h"
#include"effect_manager.h"
#include"skill.h"
#include"skill_type.h"

class Board;

class Ship
{
public:
	Ship()=default;
	~Ship() = default;

	void init_ship(SDL_Texture* texture,SDL_Point first_pos,Board* board,
					int size,int hp,int datk_time,int defense_time, SkillType skill = SkillType::NONE);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);

	const SDL_Point& get_position()const;

private:
	void set_position(const SDL_Point& pos);
	bool check_cursor_hit(int x, int y)const;
	void update_rect();
	void rotate_ship();


private:

	bool have_skill = false;
	int ship_size = 0;
	int hp = 0;
	int atk_time = 0;
	int defense_time = 0;
	SkillType ship_skill = SkillType::NONE;
	Board* player_board = nullptr;

private:

	SDL_Texture* ship_texture = nullptr;

	SDL_Point absolute_position = {0};
	SDL_Point last_position = { 0 };

	SDL_Point delta = { 0 };

	SDL_Rect collision_rect = { 0 };
	SDL_Rect render_rect = { 0 };



	bool horizontal = true;
	bool ship_in_move = false;
	bool ship_rotate = false;
	bool ship_in_board = false;

};