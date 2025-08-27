#pragma once
#include<SDL.h>
#include"player.h"
#include"scene.h"
#include"button.h"
#include"number_board.h"
#include"skill_type.h"
#include<memory>
#include"scene_type.h"
#include"game_manager.h"
#include"resources_manager.h"
#include"txt_texture_manager.h"

class GameScene :public Scene
{
private:

	NumberBoard number_board_prototype;

	std::unique_ptr<NumberBoard> missile_count;
	std::unique_ptr<NumberBoard> skill_count;


	int missile_num = 0;
	int skill_time = 0;

	Button missile_button;
	Button Detect_3x3_button;
	Button Detect_13C_button;
	Button Attack_5C_button;
	Button Attack_3x3_button;
	Button Repair_button;
	
	SkillType current_skill_type = SkillType::NONE;
	Button* current_button;

	std::vector<Button*> skill_button_list;

	int round_time = 0;
	int missile_add = 0;

private:


	Player* p1 = nullptr;
	Player* p2 = nullptr;
	Player* current_player = nullptr;
	Player* current_update_player = nullptr;


	SDL_Texture* text_player1 = nullptr;
	SDL_Texture* text_player2 = nullptr;

	SDL_Rect player1_text_rect = { 180,300,300,80 };
	SDL_Rect player2_text_rect = { 800,300,300,80 };

	Button next_player_button;

public:
	GameScene();
	~GameScene();

	void on_enter();
	void on_exit();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);

	void reset_all_button();
	Player* get_other_player();
	void next_player_turn();
};