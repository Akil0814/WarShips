#pragma once
#include"manager.h"
#include<iostream>

#include "scene_manager.h"
#include"atlas_manager.h"
#include"scene_pool.h"
#include"scene_type.h"
#include"player.h"


#include<SDL.h>
#include <SDL_ttf.h>//×ÖÌå¿â
#include <SDL_mixer.h>//ÒôÆµ¿â
#include <SDL_image.h>//Í¼Ïñ¿â
#include <SDL2_gfxPrimitives.h>


class GameManager :public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv);

	void switch_scene(SceneType type);

	void create_player();
	void destroy_player();

	SDL_Renderer* get_renderer()const;
	SDL_Window* get_window()const;

	Player* get_player1();
	Player* get_player2();

protected:
	GameManager();
	~GameManager();

private:

	void on_input(const SDL_Event& event);
	void on_update(double delta);
	void on_render();

	void init_assert(bool flag, const char* err_msg)
	{
		if (flag)
			return;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Game Start Error", err_msg, window);
		exit(-1);
	}

private:

	const int FPS = 30;
	bool is_quit = false;

	SDL_Event event;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Scene* menu_scene = nullptr;

	Player* player1 = nullptr;
	Player* player2 = nullptr;

};

