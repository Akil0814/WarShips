#include"game_scene.h"

#include<assert.h>

GameScene::GameScene():
	next_player_button({ 1100,650,150,50 }, { 1105,655,140,40 },
	TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "next player"),
	ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr),

	missile_button({ 30,650,50,50 }, { 30,652,50,45 },
		 ResourcesManager::instance()->get_texture(ResID::Tex_Atk_Time),
		 ResourcesManager::instance()->get_sound(ResID::Sound_Click), nullptr)
{

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

	missile_count->set_rect_for_ones_place({ 105,655,30,40 });


	skill_num_board_list.push_back(missile_count.get());


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

	skill_button_list.push_back(&missile_button);

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
	p1 = GameManager::instance()->get_player1();
	p2 = GameManager::instance()->get_player2();

	current_player = p1;
	current_player->set_board_pos({ 30,30 });
	get_other_player()-> set_board_pos({ 650,30 });

	missile_num = current_player->get_atk_time();
	missile_count->set_number(missile_num);


	next_player_button.set_on_click([this]
		{
				next_player_turn();
		});

	Mix_FadeInMusic(ResourcesManager::instance()->get_music(ResID::Music_In_Game), -1,3000);
}

void GameScene::on_exit()
{
	Mix_HaltMusic();
}

void GameScene::on_update(double delta)
{
	next_player_button.on_update(delta);
	get_other_player()->on_update(delta);
}

void GameScene::on_render(SDL_Renderer* renderer)
{
	next_player_button.on_render(renderer);

	current_player->on_render(renderer);
	current_player->draw_cover(renderer);
	get_other_player()->on_render(renderer);

	for (auto& iter : skill_button_list)
		iter->on_render(renderer);

	for (auto& iter : skill_num_board_list)
		iter->on_render(renderer);

	if (current_player == p1)
	{
		SDL_RenderCopy(renderer, text_player1, nullptr, &player1_text_rect);
	}
	else
	{
		SDL_RenderCopy(renderer, text_player2, nullptr, &player2_text_rect);
	}

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}

void GameScene::on_input(const SDL_Event& event)
{
	if(missile_num!=0)
		get_other_player()->on_input(event);

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

void GameScene::next_player_turn()
{
	current_player == p1 ? current_player=p2 : current_player=p1;
	missile_num = current_player->get_atk_time();
	missile_count->set_number(missile_num);
}
