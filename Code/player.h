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


	virtual void on_input(const SDL_Event& event);
	virtual void on_input(const SDL_Event& event, bool setup);
	bool finish_round();


	void draw_cover(SDL_Renderer* renderer);
	void set_board_pos(SDL_Point pos);

private:

	bool is_win = false;
	bool have_ship_in_move = false;


	Ship* current_ship = nullptr;
	SDL_Point current_ship_last_pos = {0,0};
	bool current_ship_last_hor_state = true;


	std::vector<Ship*> ship_list;
	Board board;
};

