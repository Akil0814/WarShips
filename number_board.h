#pragma once
#include <SDL.h>
#include<vector>
#include<iostream>
#include<functional>

#include"timer.h"

class NumberBoard
{
public:
	void on_render(SDL_Renderer* renderer);
	void on_update(double delta);
	void set_number(int val);

	void set_rect_for_ones_place(SDL_Rect rect);
	bool init_texture(std::initializer_list<SDL_Texture*> textures);

private:

	SDL_Rect first_digits = {0};
	std::vector<int> digits;
	std::vector<SDL_Rect> digit_rect;
	std::vector<SDL_Texture*> texture_list;
};