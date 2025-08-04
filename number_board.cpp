#include"number_board.h"

void NumberBoard::on_render(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < digits.size(); ++i)
	{

		int digit = digits[i];
		SDL_Texture* tex = texture_list[digit];
		SDL_RenderCopy(renderer, tex, nullptr, &digit_rect[i]);
	}
}

void NumberBoard::on_update(double delta)
{

}

void NumberBoard::set_number(int val)
{
	digits.clear();
	digit_rect.clear();

	if (val == 0)
		digits.push_back(0);
	else
	{
		while (val > 0)
		{
			digits.push_back(val % 10);
			val /= 10;
		}
	}

	for (size_t i = 0; i < digits.size(); ++i)
	{
		digit_rect.push_back(SDL_Rect{ first_digits.x - (int)(i * (first_digits.w)), first_digits.y, first_digits.w, first_digits.h });
	}
}

void NumberBoard::set_rect_for_ones_place(SDL_Rect rect)
{
	first_digits = rect;
	digits.clear();
	digit_rect.clear();
}

bool NumberBoard::init_texture(std::initializer_list<SDL_Texture*> textures)
{
	if (textures.size() == 0)
		return false;

	for (auto tex : textures)
	{
		if (tex == nullptr)
			return false;
		texture_list.push_back(tex);
	}

	if (texture_list.size() < 10)
	{
		std::cout<<"[NumberBoard] Error: Missing digit textures!  got:" << texture_list.size() << std::endl;
		return false;
	}

	return true;
}


