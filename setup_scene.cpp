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

	get_LightCruiser({ 665, 415, 120,  40 },{ 665, 415, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_2),nullptr, nullptr),
	get_HeavyCruiser({ 665, 475, 120,  40 },{ 665, 475, 120,  40 }, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_2),nullptr, nullptr),
	get_SuperCruiser({ 665, 535, 120,  40 },{ 665, 535, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_2),nullptr, nullptr),
	get_BattleCruiser({ 665, 595, 160,  40 },{ 665, 595, 160,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_4),nullptr, nullptr),

	get_AviationBattleship({ 805, 415, 200,  40 },{ 805, 415, 200,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_5),nullptr, nullptr),
	get_AircraftCarrier({ 805, 475, 200,  40 },{ 805, 475, 200,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_5),nullptr, nullptr),
	get_LightCarrier({ 805, 535, 200,  40 },{ 805, 535, 200,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_5),nullptr, nullptr),
	get_Battleship({ 845, 595, 160,  40 },{ 845, 595, 160,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_4),nullptr, nullptr),

	get_Destroyer({ 1025, 415,  80,  40 },{ 1025, 415,  80,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_1),nullptr, nullptr),
	get_Submarine({ 1025, 475, 120,  40 },{ 1025, 475, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_3),nullptr, nullptr),
	get_RepairShip({ 1025, 535, 120,  40 },{ 1025, 535, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_3),nullptr, nullptr)
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

	reset_button.set_on_click([]{});

	get_Destroyer.set_on_hovered([] {std::cout << "test" << std::endl; });

	get_Destroyer.set_on_click([this]{try_add_ship(ShipType::Destroyer, 10);});


	current_player = p1;
}
void SetupScene::on_exit()
{

}

void SetupScene::on_update(double delta)
{
	get_Destroyer.on_update(delta);
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



	get_Destroyer.on_render(renderer);
	get_LightCruiser.on_render(renderer);
	get_HeavyCruiser.on_render(renderer);
	get_SuperCruiser.on_render(renderer);
	get_BattleCruiser.on_render(renderer);
	get_Battleship.on_render(renderer);
	get_AviationBattleship.on_render(renderer);
	get_AircraftCarrier.on_render(renderer);
	get_LightCarrier.on_render(renderer);
	get_Submarine.on_render(renderer);
	get_RepairShip.on_render(renderer);


	reset_button.on_render(renderer);

	draw_rect(renderer);

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}

void SetupScene::on_input(const SDL_Event& event)
{
	reset_button.on_input(event);
}

void SetupScene::draw_rect(SDL_Renderer* renderer)
{

	SDL_RenderDrawLine(renderer, 650, 360, 1250, 360);//market

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &side_rect);
}

void SetupScene::try_add_ship(ShipType new_ship, int cost)
{
	if (current_player->spend_coin(cost))
	{
		current_player->add_ship(ShipFactory::instance()->creat_ship(new_ship));
	}
	else
	{

	}
}
