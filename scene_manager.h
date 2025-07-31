#pragma once
#include<SDL.h>
#include"scene.h"
#include"manager.h"

class SceneManager :public Manager<SceneManager>
{
	friend class Manager<SceneManager>;
protected:

	SceneManager() = default;

	~SceneManager() = default;

public:
	void set_current_scene(Scene* scene);
	void switch_to(Scene* scene);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);

private:
	Scene* current_scene = nullptr;
};

