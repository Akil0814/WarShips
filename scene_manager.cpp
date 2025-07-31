#include "scene_manager.h"
#include<iostream>

void SceneManager::set_current_scene(Scene* scene)
{
	current_scene = scene;
	current_scene->on_enter();
}

void SceneManager::switch_to(Scene* scene)
{
	current_scene->on_exit();

	current_scene = scene;

	current_scene->on_enter();
}

void SceneManager::on_update(double delta)
{
	current_scene->on_update(delta);
}

void SceneManager::on_render(SDL_Renderer* renderer)
{
	current_scene->on_render(renderer);
}

void SceneManager::on_input(const SDL_Event& event)
{
	current_scene->on_input(event);
}

