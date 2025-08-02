#pragma once
#include<SDL.h>

#include"scene.h"
#include"player.h"
#include"button.h"
#include"scene_type.h"
#include"game_manager.h"
#include"resources_manager.h"
#include"txt_texture_manager.h"

class SetupScene :public Scene
{
private:
	Button next_button;
	Button start_button;
	Button reset_button;

	Button get_ship_test;

	SDL_Texture* text_player1 = nullptr;
	SDL_Texture* text_player2 = nullptr;
	SDL_Texture* text_shop = nullptr;


	SDL_Rect side_rect = { 650,30,600,660 };

	SDL_Rect coin_tex = { 1100,30,50,50 };

	SDL_Rect player_txt = { 660,30,90,40 };
	SDL_Rect shop_txt = { 660,360,220,40 };

	Player* p1 = nullptr;
	Player* p2 = nullptr;
	Player* current_player = nullptr;

private:
	void draw_rect(SDL_Renderer* renderer);

public:
	SetupScene();
	~SetupScene();

	void on_enter();
	void on_exit();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);
};