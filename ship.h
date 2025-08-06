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
					int size,int hp,int datk_time,int defense_time,
					SkillType skill1 = SkillType::NONE,int time_1=0,SkillType skill2 = SkillType::NONE, int time_2 = 0);

	void init_pos(SDL_Point first_pos);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);

	SkillType get_skill_1()const;
	int get_skill_1_time()const;
	SkillType get_skill_2()const;
	int get_skill_2_time()const;

	void take_damage();
	bool is_in_board()const;
	bool is_sink() const;
	int get_atk_time() const;
	bool check_motion()const;


private:
	void set_position(const SDL_Point& pos);
	bool check_cursor_hit(int x, int y)const;
	void update_rect();
	void rotate_ship();


private:

	int ship_size = 0;
	int hp = 0;
	int atk_time = 0;
	int defense_time = 0;

	SkillType skill_1 = SkillType::NONE;
	int skill1_time = 0;

	SkillType skill_2 = SkillType::NONE;
	int skill2_time = 0;

	Board* player_board = nullptr;

private:

	SDL_Texture* ship_texture = nullptr;

	SDL_Point absolute_position = {0};
	SDL_Point last_position = { 0 };

	SDL_Point delta = { 0 };

	SDL_Rect collision_rect = { 0 };
	SDL_Rect render_rect = { 0 };

	bool horizontal = true;
	bool sink = false;

	bool ship_in_move = false;
	bool ship_in_rotate = false;
	bool ship_in_board = false;

};