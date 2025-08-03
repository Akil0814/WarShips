#include"game_scene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::on_enter()
{
	p1 = GameManager::instance()->get_player1();
	p2 = GameManager::instance()->get_player2();
	text_player1 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Player1:");
	text_player2 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Player2:");
	current_player = p1;
	current_player->set_board_pos({ 650,30 });
	get_other_player()->set_board_pos({ 30,30 });
}
void GameScene::on_exit()
{

}

void GameScene::on_update(double delta)
{
	current_player->on_update(delta);
	if (current_player->finish_round())
		current_player = get_other_player();
}
void GameScene::on_render(SDL_Renderer* renderer)
{
	current_player->on_render(renderer);
	get_other_player()->on_render(renderer);
	get_other_player()->draw_cover(renderer);
	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}
void GameScene::on_input(const SDL_Event& event)
{
	current_player->on_input(event);
}

Player* GameScene::get_other_player()
{
	return current_player == p1 ? p2 : p1;
}