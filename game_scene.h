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
	std::unique_ptr<NumberBoard> Detect_3x3_count;
	std::unique_ptr<NumberBoard> Detect_13C_count;
	std::unique_ptr<NumberBoard> Attack_3L_count;
	std::unique_ptr<NumberBoard> Attack_5L_count;
	std::unique_ptr<NumberBoard> Attack_5C_count;
	std::unique_ptr<NumberBoard> Attack_3x3_count;

	int missile_num = 0;
	int Detect_3x3_num = 0;
	int Detect_13C_num=0;
	int Attack_3L_num=0;
	int Attack_5L_num=0;
	int Attack_5C_num=0;
	int Attack_3x3_num=0;

	Button missile_button;
	Button Detect_3x3_button;
	Button Detect_13C_button;
	Button Attack_3L_button;
	Button Attack_5L_button;
	Button Attack_5C_button;
	Button Attack_3x3_button;
	
	SkillType current_skill_type = SkillType::NONE;
	Button* current_button;

	std::vector<Button*> skill_button_list;
	std::vector<NumberBoard*> skill_num_board_list;

private:

	Player* p1 = nullptr;
	Player* p2 = nullptr;
	Player* current_player = nullptr;

	SDL_Texture* text_player1 = nullptr;
	SDL_Texture* text_player2 = nullptr;

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
};