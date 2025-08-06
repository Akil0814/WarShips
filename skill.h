#pragma once
#include<SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include<string>
#include<iostream>
#include<functional>

class Skill
{
public:
	Skill();
	~Skill();

	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& event);
	void on_update(double delta);

	void set_on_click(std::function<void()> func);
	void set_on_hovered(std::function<void()> func);

private:
	//Button skill_button;
	int skill_time=0;
};
