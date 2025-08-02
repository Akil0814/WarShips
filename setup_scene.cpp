#include"setup_scene.h"

SetupScene::SetupScene()
	:next_button({ 800,500,100,50 }, { 815,505,70,40 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "NEXT"),
		nullptr, nullptr),
	start_button({ 800,500,100,50 }, { 815,505,70,40 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "START"),
		nullptr, nullptr),
	reset_button({ 500,650,80,40 }, { 505,655,70,30 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Reset"),
		nullptr, nullptr),
	get_ship_test({ 680,650,150,30 }, { 680,650,150,30 }, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_5),nullptr,nullptr)
{
}

SetupScene::~SetupScene()
{

}

void SetupScene::on_enter()
{
	WINDOW_WIDTH = 1280;
	WINDOW_HEIGHT = 720;
	SDL_SetWindowSize(GameManager::instance()->get_window(), WINDOW_WIDTH, WINDOW_HEIGHT);
	p1 = GameManager::instance()->get_player1();
	p2 = GameManager::instance()->get_player2();
	text_player1 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Player1:");
	text_player2 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Player2:");
	text_shop = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Shop: click to buy");

	reset_button.set_on_click([this]
		{

		});
	get_ship_test.set_on_hovered([] {std::cout << "test" << std::endl; });
	get_ship_test.set_on_click([] {std::cout << "test2" << std::endl; });

	current_player = p1;
}
void SetupScene::on_exit()
{

}

void SetupScene::on_update(double delta)
{
	get_ship_test.on_update(delta);
}

void SetupScene::on_render(SDL_Renderer* renderer)
{
	current_player->on_render(renderer, true);

	if(current_player==p1)
		SDL_RenderCopy(renderer, text_player1,nullptr, &player_txt);
	else
		SDL_RenderCopy(renderer, text_player2, nullptr, &player_txt);

	SDL_RenderCopy(renderer, text_shop, nullptr, &shop_txt);
	SDL_RenderCopy(renderer,ResourcesManager::instance()->get_texture(ResID::Tex_Coin), nullptr, &coin_tex);


	get_ship_test.on_render(renderer);
	reset_button.on_render(renderer);

	draw_rect(renderer);

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}

void SetupScene::on_input(const SDL_Event& event)
{
	get_ship_test.on_input(event);
	reset_button.on_input(event);
}

void SetupScene::draw_rect(SDL_Renderer* renderer)
{

	//SDL_RenderDrawLine(renderer, 650,70,1250,70);
	SDL_RenderDrawLine(renderer, 650, 360, 1250, 360);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &side_rect);
}
