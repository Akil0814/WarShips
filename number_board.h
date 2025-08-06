#pragma once
#include <SDL.h>
#include<vector>
#include<iostream>
#include<functional>
#include<memory>

#include"timer.h"

class NumberBoard
{
public:
	void on_render(SDL_Renderer* renderer);
	void on_update(double delta);
	void set_number(int val);

	void set_rect_for_ones_place(SDL_Rect rect);
	bool init_texture(std::initializer_list<SDL_Texture*> textures);

	std::unique_ptr<NumberBoard> clone() const
	{
		auto board_clone = std::make_unique<NumberBoard>();

		board_clone->first_digits = this->first_digits;
		board_clone->digits = this->digits;
		board_clone->digit_rect = this->digit_rect;
		board_clone->texture_list = this->texture_list;

		return board_clone;
	}

	int get_number_on_board();

private:

	int number = 0;
	SDL_Rect first_digits = {0};
	std::vector<int> digits;
	std::vector<SDL_Rect> digit_rect;
	std::vector<SDL_Texture*> texture_list;
};