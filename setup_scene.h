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

	Button get_ship_test;

	SDL_Texture* text_player1 = nullptr;
	SDL_Texture* text_player2 = nullptr;

	SDL_Rect player_ship;
	SDL_Rect ship_market;
	SDL_Rect other_market;

	Player* p1 = nullptr;
	Player* p2 = nullptr;
	Player* current_player = nullptr;

public:
	SetupScene();
	~SetupScene();

	void on_enter();
	void on_exit();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);
};