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
	shop_item_list.push_back(&get_LightCruiser);
	shop_item_list.push_back(&get_HeavyCruiser);
	shop_item_list.push_back(&get_SuperCruiser);
	shop_item_list.push_back(&get_BattleCruiser);

	shop_item_list.push_back(&get_AviationBattleship);
	shop_item_list.push_back(&get_AircraftCarrier);
	shop_item_list.push_back(&get_LightCarrier);
	shop_item_list.push_back(&get_Battleship);

	shop_item_list.push_back(&get_Destroyer);
	shop_item_list.push_back(&get_Submarine);
	shop_item_list.push_back(&get_RepairShip);
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


	get_Destroyer.set_on_hovered([this] {current_view_ship= ShipType::Destroyer; });
	get_LightCruiser.set_on_hovered([this] {current_view_ship = ShipType::LightCruiser; });
	get_HeavyCruiser.set_on_hovered([this] {current_view_ship = ShipType::HeavyCruiser; });
	get_SuperCruiser.set_on_hovered([this] {current_view_ship = ShipType::SuperCruiser; });
	get_BattleCruiser.set_on_hovered([this] {current_view_ship = ShipType::BattleCruiser; });
	get_Battleship.set_on_hovered([this] {current_view_ship = ShipType::Battleship; });
	get_AviationBattleship.set_on_hovered([this] {current_view_ship = ShipType::AviationBattleship; });
	get_AircraftCarrier.set_on_hovered([this] {current_view_ship = ShipType::AircraftCarrier; });
	get_LightCarrier.set_on_hovered([this] {current_view_ship = ShipType::LightCarrier; });
	get_Submarine.set_on_hovered([this] {current_view_ship = ShipType::Submarine; });
	get_RepairShip.set_on_hovered([this] {current_view_ship = ShipType::RepairShip; });


	get_Destroyer.set_on_click([this] { try_add_ship(ShipType::Destroyer, 10); });
	get_LightCruiser.set_on_click([this] { try_add_ship(ShipType::LightCruiser, 10); });
	get_HeavyCruiser.set_on_click([this] { try_add_ship(ShipType::HeavyCruiser, 10); });
	get_SuperCruiser.set_on_click([this] { try_add_ship(ShipType::SuperCruiser, 10); });
	get_BattleCruiser.set_on_click([this] { try_add_ship(ShipType::BattleCruiser, 10); });
	get_Battleship.set_on_click([this] { try_add_ship(ShipType::Battleship, 10); });
	get_AviationBattleship.set_on_click([this] { try_add_ship(ShipType::AviationBattleship, 10); });
	get_AircraftCarrier.set_on_click([this] { try_add_ship(ShipType::AircraftCarrier, 10); });
	get_LightCarrier.set_on_click([this] { try_add_ship(ShipType::LightCarrier, 10); });
	get_Submarine.set_on_click([this] { try_add_ship(ShipType::Submarine, 10); });
	get_RepairShip.set_on_click([this] { try_add_ship(ShipType::RepairShip, 10); });

	current_player = p1;
}
void SetupScene::on_exit()
{

}

void SetupScene::on_update(double delta)
{
	for (auto& iter : shop_item_list)
		iter->on_update(delta);
	current_player->on_update(delta,true);
}

void SetupScene::on_render(SDL_Renderer* renderer)
{
	current_player->on_render(renderer, true);
	reset_button.on_render(renderer);
	if(current_player==p1)
		SDL_RenderCopy(renderer, text_player1,nullptr, &player_txt);
	else
		SDL_RenderCopy(renderer, text_player2, nullptr, &player_txt);

	for (auto& iter : shop_item_list)
		iter->on_render(renderer);

	for (auto& iter : shop_item_list)
	{
		if (iter->get_status() == Button::Status::Hovered)
		{
			switch (current_view_ship)
			{
			case ShipType::Destroyer:
				SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);

				break;
			case ShipType::LightCruiser:
				SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);

				break;
			case ShipType::HeavyCruiser:
				SDL_SetRenderDrawColor(renderer, 0,200, 0, 255);

				break;
			case ShipType::SuperCruiser:

				break;
			case ShipType::BattleCruiser:

				break;
			case ShipType::Battleship:

				break;
			case ShipType::AviationBattleship:

				break;
			case ShipType::AircraftCarrier:

				break;
			case ShipType::LightCarrier:

				break;
			case ShipType::Submarine:

				break;
			case ShipType::RepairShip:

				break;
			default:
				break;
			}

			SDL_Rect test = { 100,100,500,500 };
			SDL_RenderFillRect(renderer, &test);
		}
	}

	SDL_RenderCopy(renderer, text_shop, nullptr, &shop_txt);
	SDL_RenderCopy(renderer,ResourcesManager::instance()->get_texture(ResID::Tex_Coin), nullptr, &coin_tex);


	draw_rect(renderer);

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}

void SetupScene::on_input(const SDL_Event& event)
{
	reset_button.on_input(event);
	for (auto& iter : shop_item_list)
		iter->on_input(event);
	current_player->on_input(event,true);
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
		current_player->add_ship(ShipFactory::instance()->creat_ship(new_ship,current_player->get_board()));
	}
	else
	{

	}
	std::cout << "test2" << std::endl;
}


