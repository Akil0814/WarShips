#include"menu_scene.h"

MenuScene::MenuScene()
	:button_start({ 100,50,200,70 }, { 100,50,200,70 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_128), "   Start   "),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click_Down), ResourcesManager::instance()->get_sound(ResID::Sound_Click_Up))
{
	button_start.set_on_click([]
		{
			GameManager::instance()->create_player();
			GameManager::instance()->switch_scene(SceneType::Setup);
		});
}

MenuScene::~MenuScene() = default;

void MenuScene::on_enter()
{

}
void MenuScene::on_exit() {}

void MenuScene::on_update(double delta) {}

void MenuScene::on_render(SDL_Renderer* renderer)
{
	button_start.on_render(renderer);

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}
void MenuScene::on_input(const SDL_Event& event)
{
	button_start.on_input(event);
}