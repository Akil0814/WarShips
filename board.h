#pragma once
#include<vector>
#include <SDL.h>
#include<iostream>

#include"ship.h"

#include"tile.h"
#include"bullet.h"
#include"animation.h"
#include"resources_manager.h"
#include"effect_manager.h"

class Board
{
	typedef std::vector<std::vector<Tile>> TileBoard;

public:
	Board();
	~Board();

	void on_render(SDL_Renderer* renderer);
	void on_update(double delta);
	void on_input(const SDL_Event& event);


	void set_size(int row, int col);
	void set_board_pos(SDL_Point point);

	bool place_ship(Ship* ship,SDL_Point pos, int ship_size, bool is_horizontal);
	void move_ship(SDL_Point pos, int ship_size, bool is_horizontal);

	bool is_inside(int x, int y) const;
	bool check_available(int x,int y, int ship_size, bool is_horizontal);
	bool finish_hit_time()const;
	void reset_hit_time();

	static SDL_Texture* tile_hit;
	static SDL_Texture* tile_miss;

	void show_board();////////////////////////////////

	void draw_cover(SDL_Renderer* renderer);

private:

	void draw_board(SDL_Renderer* renderer);
	void on_mouse_click(const SDL_Event& e);
	void on_mouse_move(const SDL_Event& e);

private:
	bool on_animation = false;

	bool move_in_board = false;
	bool click_in_board = false;

	bool find_target = false;
	bool finish_hit = false;

	int board_render_x = 0;
	int board_render_y = 0;

	int index_x = 0;
	int index_y = 0;

	int row = 20;
	int col = 20;

	TileBoard board;

	SDL_Point mouse_pos = {0};
	SDL_Point mouse_click_tile_center = {0};

	SDL_Rect rect_select_target;
	SDL_Rect rect_water_splash;
	SDL_Rect rect_explosion_target;

};
