#pragma once
#include<vector>
#include"board.h"
#include"ship.h"

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

	bool finish_round();

	void draw_cover(SDL_Renderer* renderer);
	void set_board_pos(SDL_Point pos);

private:

	bool is_win = false;
	bool have_ship_in_move = false;
	bool current_ship_last_hor_state = true;

	Ship* current_ship = nullptr;

	std::vector<Ship*> ship_list;
	Board board;
};

