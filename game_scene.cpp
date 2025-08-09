#include"game_scene.h"

#include<assert.h>

GameScene::GameScene():
	next_player_button({ 1100,650,150,50 }, { 1105,655,140,40 },
	TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "next player"),
	ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	missile_button({ 30,650,50,50 }, { 30,652,50,45 },
		 ResourcesManager::instance()->get_texture(ResID::Tex_Atk_Time),
		 ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

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
{
	/////////////////////////////////////////////////////////////////////////////

	number_board_prototype.init_texture({ ResourcesManager::instance()->get_texture(ResID::Tex_Num_0),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_1),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_2),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_3),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_4),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_5),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_6),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_7),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_8),
	ResourcesManager::instance()->get_texture(ResID::Tex_Num_9) });

	missile_count=number_board_prototype.clone();
	Detect_3x3_count=number_board_prototype.clone();
	Detect_13C_count=number_board_prototype.clone();
	Attack_3L_count=number_board_prototype.clone();
	Attack_5L_count=number_board_prototype.clone();
	Attack_5C_count=number_board_prototype.clone();
	Attack_3x3_count=number_board_prototype.clone();

	missile_count->set_rect_for_ones_place({ 105,655,30,40 });
	Detect_3x3_count->set_rect_for_ones_place({ 255,655,30,40 });
	Detect_13C_count->set_rect_for_ones_place({ 405,655,30,40 });
	Attack_3L_count->set_rect_for_ones_place({ 555,655,30,40 });
	Attack_5L_count->set_rect_for_ones_place({ 705,655,30,40 });
	Attack_5C_count->set_rect_for_ones_place({ 855,655,30,40 });
	Attack_3x3_count->set_rect_for_ones_place({ 1005,655,30,40 });

	skill_num_board_list.push_back(missile_count.get());
	skill_num_board_list.push_back(Detect_3x3_count.get());
	skill_num_board_list.push_back(Detect_13C_count.get());
	skill_num_board_list.push_back(Attack_3L_count.get());
	skill_num_board_list.push_back(Attack_5L_count.get());
	skill_num_board_list.push_back(Attack_5C_count.get());
	skill_num_board_list.push_back(Attack_3x3_count.get());

	for (auto& iter : skill_num_board_list)
	{
		iter->set_number(0);
	}

	//////////////////////////////////////////

	missile_button.set_on_click([this]
		{
			reset_all_button();
			missile_button.set_on_holed();
			missile_button.set_status(Button::Status::Pushed);
		});

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

	skill_button_list.push_back(&missile_button);
	skill_button_list.push_back(&Detect_3x3_button);
	skill_button_list.push_back(&Detect_13C_button);
	skill_button_list.push_back(&Attack_3L_button);
	skill_button_list.push_back(&Attack_5L_button);
	skill_button_list.push_back(&Attack_5C_button);
	skill_button_list.push_back(&Attack_3x3_button);

	std::cout << "creat scene" << std::endl;

	text_player1 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_256), "Player1 Turn");
	std::cout << "creat scene2" << std::endl;

	text_player2 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_256), "Player2 Turn");
	std::cout << "creat scene3" << std::endl;


}

GameScene::~GameScene()
{
}

void GameScene::on_enter()
{
	std::cout << "on_enter1" << std::endl;


	p1 = GameManager::instance()->get_player1();
	p2 = GameManager::instance()->get_player2();

	SDL_Renderer* renderer = GameManager::instance()->get_renderer();
	TTF_Font* font = ResourcesManager::instance()->get_font(ResID::Font_256);

	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "Font: " << font << "\n";



	current_player = p1;
	current_player->set_board_pos({ 30,30 });
	get_other_player()-> set_board_pos({ 650,30 });

	std::cout << "on_enter2" << std::endl;


	next_player_button.set_on_click([this]
		{
			current_player = get_other_player();
			missile_count->set_number(current_player->get_atk_time());
		});

	missile_count->set_number(current_player->get_atk_time());
	std::cout << "on_enter3" << std::endl;


	Mix_FadeInMusic(ResourcesManager::instance()->get_music(ResID::Music_In_Game), -1,3000);

	std::cout << "on_enter4" << std::endl;


}
void GameScene::on_exit()
{
	Mix_HaltMusic();
}

void GameScene::on_update(double delta)
{
	next_player_button.on_update(delta);
	current_player->on_update(delta);
}
void GameScene::on_render(SDL_Renderer* renderer)
{
	next_player_button.on_render(renderer);
	
	current_player->on_render(renderer);
	get_other_player()->on_render(renderer);
	get_other_player()->draw_cover(renderer);

	for (auto& iter : skill_button_list)
		iter->on_render(renderer);

	for (auto& iter : skill_num_board_list)
		iter->on_render(renderer);

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}
void GameScene::on_input(const SDL_Event& event)
{
	current_player->on_input(event);
	next_player_button.on_input(event);

	for (auto iter : skill_button_list)
		iter->on_input(event);
}

Player* GameScene::get_other_player()
{
	return current_player == p1 ? p2 : p1;
}

void GameScene::reset_all_button()
{
	current_skill_type = SkillType::NONE;
	for (auto& iter : skill_button_list)
	{
		iter->set_status(Button::Status::Idle);
		iter->reset_on_holed();
	}
}
