#pragma once
#include<unordered_map>
#include"board.h"
#include"ship.h"
#include"skill_type.h"


class Player
{
public:
	Player();
	~Player();

	void on_render(SDL_Renderer* renderer);
	void on_render(SDL_Renderer* renderer,bool set_up);

	void on_update(double delta, SkillType& current_skill);
	void on_update(double delta, bool setup);

	void on_input(const SDL_Event& event);
	void on_input(const SDL_Event& event, bool setup);

	void add_ship(Ship* new_ship);
	void finish_setting();
	void reset();
	bool have_remaining_ship();

	bool spend_coin(int cost);
	int get_coin();
	int get_atk_time();
	int get_skill_time(SkillType skill);
	void use_skill(SkillType skill);

	void draw_cover(SDL_Renderer* renderer);
	void set_board_pos(SDL_Point pos);
	Board* get_board();

private:

	int coin_have = 5000;

	bool is_win = false;
	bool have_ship_in_move = false;

	Ship* current_ship = nullptr;

	int atk_time = 0;
	std::vector<Ship*> ship_list;
	Board board;
};

