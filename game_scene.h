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


	int missile_num = 0;


	Button missile_button;
	
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

/*

	Button Detect_3x3_button;
	Button Detect_13C_button;
	Button Attack_3L_button;
	Button Attack_5L_button;
	Button Attack_5C_button;
	Button Attack_3x3_button;


	std::unique_ptr<NumberBoard> Detect_3x3_count;
	std::unique_ptr<NumberBoard> Detect_13C_count;
	std::unique_ptr<NumberBoard> Attack_3L_count;
	std::unique_ptr<NumberBoard> Attack_5L_count;
	std::unique_ptr<NumberBoard> Attack_5C_count;
	std::unique_ptr<NumberBoard> Attack_3x3_count;



*/


/*

Detect_3x3_button({ 180,650,50,50 }, { 180,650,50,50 },
		ResourcesManager::instance()->get_texture(ResID::Tex_Range),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	Detect_13C_button({ 330,650,50,50 }, { 330,650,50,50 },
		ResourcesManager::instance()->get_texture(ResID::Tex_Range),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	Attack_3L_button({ 480,650,50,50 }, { 480,650,50,50 },
		ResourcesManager::instance()->get_texture(ResID::Tex_Bombs),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	Attack_5L_button({ 630,650,50,50 }, { 630,650,50,50 },
		ResourcesManager::instance()->get_texture(ResID::Tex_Bombs),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	Attack_5C_button({ 780,650,50,50 }, { 780,650,50,50 },
		ResourcesManager::instance()->get_texture(ResID::Tex_Bombs),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	Attack_3x3_button({ 930,650,50,50 }, { 930,650,50,50 },
		ResourcesManager::instance()->get_texture(ResID::Tex_Bombs),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr)




	Detect_3x3_button.set_on_click([this]
		{
			reset_all_button();
			Detect_3x3_button.set_on_holed();
			Detect_3x3_button.set_status(Button::Status::Pushed);


		});

	Detect_13C_button.set_on_click([this]
		{
			reset_all_button();
			Detect_13C_button.set_on_holed();
			Detect_13C_button.set_status(Button::Status::Pushed);


		});

	Attack_3L_button.set_on_click([this]
		{
			reset_all_button();
			Attack_3L_button.set_on_holed();
			Attack_3L_button.set_status(Button::Status::Pushed);


		});
	Attack_5L_button.set_on_click([this]
		{
			reset_all_button();
			Attack_5L_button.set_on_holed();
			Attack_5L_button.set_status(Button::Status::Pushed);


		});
	Attack_5C_button.set_on_click([this]
		{
			reset_all_button();
			Attack_5C_button.set_on_holed();
			Attack_5C_button.set_status(Button::Status::Pushed);


		});
	Attack_3x3_button.set_on_click([this]
		{
			reset_all_button();
			Attack_3x3_button.set_on_holed();
			Attack_3x3_button.set_status(Button::Status::Pushed);
		});


	skill_button_list.push_back(&Detect_3x3_button);
	skill_button_list.push_back(&Detect_13C_button);
	skill_button_list.push_back(&Attack_3L_button);
	skill_button_list.push_back(&Attack_5L_button);
	skill_button_list.push_back(&Attack_5C_button);
	skill_button_list.push_back(&Attack_3x3_button);


	Detect_3x3_count=number_board_prototype.clone();
	Detect_13C_count=number_board_prototype.clone();
	Attack_3L_count=number_board_prototype.clone();
	Attack_5L_count=number_board_prototype.clone();
	Attack_5C_count=number_board_prototype.clone();
	Attack_3x3_count=number_board_prototype.clone();

		Detect_3x3_count->set_rect_for_ones_place({ 255,655,30,40 });
	Detect_13C_count->set_rect_for_ones_place({ 405,655,30,40 });
	Attack_3L_count->set_rect_for_ones_place({ 555,655,30,40 });
	Attack_5L_count->set_rect_for_ones_place({ 705,655,30,40 });
	Attack_5C_count->set_rect_for_ones_place({ 855,655,30,40 });
	Attack_3x3_count->set_rect_for_ones_place({ 1005,655,30,40 });


	skill_num_board_list.push_back(Detect_3x3_count.get());
	skill_num_board_list.push_back(Detect_13C_count.get());
	skill_num_board_list.push_back(Attack_3L_count.get());
	skill_num_board_list.push_back(Attack_5L_count.get());
	skill_num_board_list.push_back(Attack_5C_count.get());
	skill_num_board_list.push_back(Attack_3x3_count.get());


	int Detect_3x3_num = 0;
	int Detect_13C_num=0;
	int Attack_3L_num=0;
	int Attack_5L_num=0;
	int Attack_5C_num=0;
	int Attack_3x3_num=0;


*/