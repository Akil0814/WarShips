#pragma once
#include<SDL.h>
#include"player.h"
#include"scene.h"
#include"button.h"
#include"scene_type.h"
#include"game_manager.h"
#include"resources_manager.h"
#include"txt_texture_manager.h"

class GameScene :public Scene
{
private:

	Player* p1 = nullptr;
	Player* p2 = nullptr;

	Player* current_player = nullptr;
	SDL_Texture* text_player1 = nullptr;
	SDL_Texture* text_player2 = nullptr;
public:
	GameScene();
	~GameScene();

	void on_enter();
	void on_exit();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);

	Player* get_other_player();
};