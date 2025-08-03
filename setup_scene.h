#pragma once
#include<SDL.h>

#include"scene.h"
#include"player.h"
#include"button.h"
#include"board.h"
#include"scene_type.h"
#include"ship_factory.h"
#include"ship_type.h"
#include"game_manager.h"
#include"resources_manager.h"
#include"txt_texture_manager.h"

class SetupScene :public Scene
{
private:

	Button next_button;
	Button start_button;
	Button reset_button;

	Button get_Destroyer;
	Button get_LightCruiser;
	Button get_HeavyCruiser;
	Button get_SuperCruiser;
	Button get_BattleCruiser;
	Button get_Battleship;
	Button get_AviationBattleship;
	Button get_AircraftCarrier;
	Button get_LightCarrier;
	Button get_Submarine;
	Button get_RepairShip;

	ShipType current_view_ship = ShipType::Destroyer;
	
	std::vector<Button*> shop_item_list;

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
	void try_add_ship(ShipType new_ship,int cost);
	void next_player();

public:
	SetupScene();
	~SetupScene();

	void on_enter();
	void on_exit();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);
};