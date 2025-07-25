#include "game_manager.h"

GameManager::GameManager()
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 Error");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_img Error");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer Error");
	init_assert(!TTF_Init(), u8"SDL_ttf Error");
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	window = SDL_CreateWindow("Battle Ship!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	init_assert(window, u8"SDL_CreateWindow Error");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);//硬件加速 垂直同步 目标纹理
	init_assert(renderer, u8"SDL_CreateRenderer Error");

	init_assert(ResourcesManager::instance()->load_from_file(renderer), u8"加载游戏资源失败！");
	init_assert(AtlasManager::instance()->load_atlas(), u8"加载游戏图集资源失败！");
	init_assert(EffectManager::instance()->init_all_effect(), u8"加载游戏特效资源失败！");
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int GameManager::run(int argc, char** argv)
{
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();//获取高性能计数器的频率

	SceneManager::instance()->set_current_scene(ScenePool::instance()->get_scene(SceneType::Menu));

	while (!is_quit)
	{
		while (SDL_PollEvent(&event))
			on_input(event);

		Uint64 current_counter = SDL_GetPerformanceCounter();//实现动态延时
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;

		if (delta * 1000 < 1000.0 / FPS)
			SDL_Delay((Uint32)(1000.0 / FPS - delta * 1000));

		on_update(delta);

		SDL_RenderClear(renderer);

		on_render();

		SDL_RenderPresent(renderer);
	}

	return 0;
}

void GameManager::on_input(const SDL_Event& event)
{
	SceneManager::instance()->on_input(event);
}

void GameManager::on_update(double delta)
{
	SceneManager::instance()->on_update(delta);
}

void GameManager::on_render()
{
	SceneManager::instance()->on_render(renderer);
}

SDL_Window* GameManager::get_window()const
{
	return window;
}

SDL_Renderer* GameManager::get_renderer()const
{
	return renderer;
}

void GameManager::switch_scene(SceneType type)
{
	SceneManager::instance()->switch_to(ScenePool::instance()->get_scene(type));
}

Player* GameManager::get_player1()
{
	return player1;
}

Player* GameManager::get_player2()
{
	return player2;
}