#include"settlement_scene.h"

SettlementScene::SettlementScene()
{
}

SettlementScene::~SettlementScene()
{
}

void SettlementScene::on_enter()
{
	Mix_FadeInMusic(ResourcesManager::instance()->get_music(ResID::Music_Game_End), -1, 1000);

}
void SettlementScene::on_exit()
{

}

void SettlementScene::on_update(double delta)
{

}
void SettlementScene::on_render(SDL_Renderer* renderer)
{

}
void SettlementScene::on_input(const SDL_Event& event)
{

}