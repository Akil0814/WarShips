#pragma once
#include<vector>
#include"board.h"
#include"ship.h"
#include"skill.h"
#include"skill_type.h"
#include"skill_factory.h"

class Player
{
public:
	Player();
	~Player();

	void on_render(SDL_Renderer* renderer);
	void on_render(SDL_Renderer* renderer,bool set_up);

	void on_update(double delta);
	void on_update(double delta, bool setup);

	void on_input(const SDL_Event& event);
	void on_input(const SDL_Event& event, bool setup);

	void add_ship(Ship* new_ship);
	void finish_setting();

	bool spend_coin(int cost);

	bool finish_round();

	void draw_cover(SDL_Renderer* renderer);
	void set_board_pos(SDL_Point pos);
	Board* get_board();

private:

	int coin_have = 210;

	bool is_win = false;
	bool have_ship_in_move = false;
	bool current_ship_last_hor_state = true;

	Ship* current_ship = nullptr;

	int atk_time_each_round = 0;
	std::vector<Ship*> ship_list;
	std::vector<Skill*> skill_list;

	Board board;
};

