#include"setup_scene.h"

SetupScene::SetupScene()
	:next_button({ 30,650,80,40 }, { 35,655,70,30 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "NEXT"),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click_Down), ResourcesManager::instance()->get_sound(ResID::Sound_Click_Up)),
	start_button({ 30,650,80,40 }, { 35,655,70,30 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "START"),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click_Down), ResourcesManager::instance()->get_sound(ResID::Sound_Click_Up)),
	reset_button({ 500,650,80,40 }, { 505,655,70,30 },
		TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Reset"),
		ResourcesManager::instance()->get_sound(ResID::Sound_Click_Down), ResourcesManager::instance()->get_sound(ResID::Sound_Click_Up)),

	get_LightCruiser({ 665, 415, 120,  40 },{ 665, 415, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_LightCruiser),nullptr, nullptr),
	get_HeavyCruiser({ 665, 475, 120,  40 },{ 665, 475, 120,  40 }, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_HeavyCruiser),nullptr, nullptr),
	get_SuperCruiser({ 665, 535, 120,  40 },{ 665, 535, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_SuperCruiser),nullptr, nullptr),
	get_BattleCruiser({ 665, 595, 160,  40 },{ 665, 595, 160,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_BattleCruiser),nullptr, nullptr),

	get_AviationBattleship({ 805, 415, 200,  40 },{ 805, 415, 200,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AviationBattleship),nullptr, nullptr),
	get_AircraftCarrier({ 805, 475, 200,  40 },{ 805, 475, 200,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_AircraftCarrier),nullptr, nullptr),
	get_LightCarrier({ 805, 535, 200,  40 },{ 805, 535, 200,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_LightCarrier),nullptr, nullptr),
	get_Battleship({ 845, 595, 160,  40 },{ 845, 595, 160,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Battleship),nullptr, nullptr),

	get_Destroyer({ 1025, 415,  80,  40 },{ 1025, 415,  80,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Destroyer),nullptr, nullptr),
	get_Submarine({ 1025, 475, 120,  40 },{ 1025, 475, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Submarine),nullptr, nullptr),
	get_RepairShip({ 1025, 535, 120,  40 },{ 1025, 535, 120,  40 },ResourcesManager::instance()->get_texture(ResID::Tex_Ship_RepairShip),nullptr, nullptr)
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

	player_coin_num.init_texture({ ResourcesManager::instance()->get_texture(ResID::Tex_Num_0),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_1),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_2),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_3),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_4),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_5),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_6),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_7),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_8),
		ResourcesManager::instance()->get_texture(ResID::Tex_Num_9) });

	player_coin_num.set_rect_for_ones_place({ 1210,35,30,40 });

}

SetupScene::~SetupScene()
{

}

void SetupScene::on_enter()
{
	p1 = GameManager::instance()->get_player1();
	p2 = GameManager::instance()->get_player2();
	text_player1 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Player1:");
	text_player2 = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Player2:");
	text_shop = TxtTextureManager::instance()->get_txt_texture(GameManager::instance()->get_renderer(), ResourcesManager::instance()->get_font(ResID::Font_72), "Shop: click to buy");

	next_button.set_on_click([this]
		{
			current_player->finish_setting();
			ShipFactory::instance()->reset_pos();
			next_player();
			player_coin_num.set_number(current_player->get_coin());
		});
	start_button.set_on_click([this]
		{
			current_player->finish_setting();
			ShipFactory::instance()->reset_pos();
			GameManager::instance()->switch_scene(SceneType::Game);
		});
	reset_button.set_on_click([this]
		{
			current_player->reset();
			player_coin_num.set_number(current_player->get_coin());
			ShipFactory::instance()->reset_pos();
		});


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


	get_Destroyer.set_on_click([this] { try_add_ship(ShipType::Destroyer, 250); });
	get_LightCruiser.set_on_click([this] { try_add_ship(ShipType::LightCruiser, 300); });
	get_HeavyCruiser.set_on_click([this] { try_add_ship(ShipType::HeavyCruiser, 350); });
	get_SuperCruiser.set_on_click([this] { try_add_ship(ShipType::SuperCruiser, 750); });
	get_BattleCruiser.set_on_click([this] { try_add_ship(ShipType::BattleCruiser, 700); });
	get_Battleship.set_on_click([this] { try_add_ship(ShipType::Battleship, 950); });
	get_AviationBattleship.set_on_click([this] { try_add_ship(ShipType::AviationBattleship, 1250); });
	get_AircraftCarrier.set_on_click([this] { try_add_ship(ShipType::AircraftCarrier, 1250); });
	get_LightCarrier.set_on_click([this] { try_add_ship(ShipType::LightCarrier, 850); });
	get_Submarine.set_on_click([this] { try_add_ship(ShipType::Submarine, 450); });
	get_RepairShip.set_on_click([this] { try_add_ship(ShipType::RepairShip, 300); });

	current_player = p1;
	player_coin_num.set_gap(10);
	player_coin_num.set_number(current_player->get_coin());

	Mix_FadeInMusic(ResourcesManager::instance()->get_music(ResID::Music_Setup),-1,3000);
}

void SetupScene::on_exit()
{
	Mix_HaltMusic();
	p1->finish_setting();
	p2->finish_setting();
}

void SetupScene::on_update(double delta)
{
	for (auto& iter : shop_item_list)
		iter->on_update(delta);
	current_player->on_update(delta,true);
	player_coin_num.on_update(delta);
}

void SetupScene::on_render(SDL_Renderer* renderer)
{
	player_coin_num.on_render(renderer);

	if (current_player == p1)
		next_button.on_render(renderer);
	else
		start_button.on_render(renderer);

	reset_button.on_render(renderer);
	if(current_player==p1)
		SDL_RenderCopy(renderer, text_player1,nullptr, &player_txt);
	else
		SDL_RenderCopy(renderer, text_player2, nullptr, &player_txt);

	SDL_RenderCopy(renderer, text_shop, nullptr, &shop_txt);
	SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Coin), nullptr, &coin_tex);

	for (auto& iter : shop_item_list)
		iter->on_render(renderer);

	current_player->on_render(renderer, true);

	for (auto& iter : shop_item_list)
	{
		static SDL_Rect test = { 50,30,525,600 };
		if (iter->get_status() == Button::Status::Hovered)
		{
			switch (current_view_ship)
			{
			case ShipType::Destroyer:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_Destroyer), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_Destroyer), nullptr, &test);
				break;
			case ShipType::LightCruiser:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_LightCruiser), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_LightCruiser), nullptr, &test);
				break;
			case ShipType::HeavyCruiser:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_HeavyCruiser), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_HeavyCruiser), nullptr, &test);
				break;
			case ShipType::SuperCruiser:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_SuperCruiser), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_SuperCruiser), nullptr, &test);
				break;
			case ShipType::BattleCruiser:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_BattleCruiser), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_BattleCruiser), nullptr, &test);
				break;
			case ShipType::Battleship:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_Battleship), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_Battleship), nullptr, &test);
				break;
			case ShipType::AviationBattleship:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_AviationBattleship), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_AviationBattleship), nullptr, &test);
				break;
			case ShipType::AircraftCarrier:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_AircraftCarrier), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_AircraftCarrier), nullptr, &test);
				break;
			case ShipType::LightCarrier:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_LightCarrier), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_LightCarrier), nullptr, &test);
				break;
			case ShipType::Submarine:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_Submarine), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_Submarine), nullptr, &test);
				break;
			case ShipType::RepairShip:
				SDL_SetTextureAlphaMod(ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_RepairShip), 210);
				SDL_RenderCopy(renderer, ResourcesManager::instance()->get_texture(ResID::Tex_Ship_Infrom_RepairShip), nullptr, &test);
				break;
			default:
				break;
			}

		}
	}

	draw_rect(renderer);

	SDL_SetRenderDrawColor(renderer, back_ground_color.r, back_ground_color.g, back_ground_color.b, back_ground_color.a);
}

void SetupScene::on_input(const SDL_Event& event)
{
	reset_button.on_input(event);
	for (auto& iter : shop_item_list)
		iter->on_input(event);
	current_player->on_input(event,true);

	if (current_player == p1)
		next_button.on_input(event);
	else
		start_button.on_input(event);
}

void SetupScene::draw_rect(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 650, 360, 1250, 360);//market
	SDL_RenderDrawRect(renderer, &side_rect);
}

void SetupScene::try_add_ship(ShipType new_ship, int cost)
{

	if (current_player->spend_coin(cost))
	{
		Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Coin), 0);
		current_player->add_ship(ShipFactory::instance()->creat_ship(new_ship,current_player->get_board()));
		player_coin_num.set_number(current_player->get_coin());
	}
	else
	{
		player_coin_num.flash_once();
		Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Error), 0);
	}
}

void SetupScene::next_player()
{
	current_player == p1 ? current_player = p2 : current_player = p1;
}

