#pragma once
#include<SDL.h>
#include"effect_manager.h"

class Ship
{
public:
	Ship()=default;
	~Ship() = default;

	void init_ship(SDL_Texture* texture, int size, SDL_Point first_pos);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);

	void set_position(const SDL_Point& pos);

	void rotate_ship();

	int get_ship_size()const;
	bool is_horizontal()const;
	const SDL_Point& get_position()const;
	bool check_motion()const;
	bool check_rotate()const;

	bool check_cursor_hit(int x, int y)const;
	void update_rect();

private:

	SDL_Texture* ship_texture = nullptr;

	SDL_Point absolute_position = {0};
	
	SDL_Rect collision_rect = { 0 };
	SDL_Rect render_rect = { 0 };

	int dx = 0;
	int dy = 0;

	int hp = 0;
	int ship_size = 0;

	bool horizontal = true;
	bool ship_in_move = false;
	bool ship_rotate = false;

};