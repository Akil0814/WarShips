#include "button.h"

Button::Button(SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
	Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up)
{
	this->rect_button = rect_button;

	if (texture_message != nullptr)
	{
		have_message = true;
		this->rect_message = rect_message;
		this->texture_message = texture_message;
	}

	if (sound_effect_down != nullptr)
	{
		have_sound_effect_down = true;
		this->sound_effect_down = sound_effect_down;
	}

	if (sound_effect_up != nullptr)
	{
		have_sound_effect_up = true;
		this->sound_effect_up = sound_effect_up;
	}


}

Button::Button(SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
	Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up,
	SDL_Color color_idle, SDL_Color color_hovered, SDL_Color color_pushed, SDL_Color color_frame)
	:Button(rect_button, rect_message, texture_message, sound_effect_down, sound_effect_up)
{
	this->color_idle = color_idle;
	this->color_hovered = color_hovered;
	this->color_pushed = color_pushed;
	this->color_frame = color_frame;
}

Button::Button(SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
	Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up,
	SDL_Texture* texture_idle, SDL_Texture* texture_hovered, SDL_Texture* texture_pushed)
	:Button(rect_button, rect_message, texture_message, sound_effect_down, sound_effect_up)
{
	init_assert<SDL_Texture>(texture_idle, "Butten Texture_idle Error");
	init_assert<SDL_Texture>(texture_hovered, "Butten Texture_hovered Error");
	init_assert<SDL_Texture>(texture_pushed, "Butten Texture_pushed Error");
	have_texture = true;

	this->texture_idle = texture_idle;
	this->texture_hovered = texture_hovered;
	this->texture_pushed = texture_pushed;
}

template<typename T>
void Button::init_assert(T* ptr, const std::string& err_msg)const
{
	if (ptr == nullptr)
	{
		std::cout << err_msg << std::endl;
		exit(-1);
	}
}

void Button::on_render(SDL_Renderer* renderer)
{
	if (!have_texture)
	{
		switch (status)
		{
		case Status::Idle:
			SDL_SetRenderDrawColor(renderer, color_idle.r, color_idle.g, color_idle.b, color_idle.a);
			break;
		case Status::Hovered:
			SDL_SetRenderDrawColor(renderer, color_hovered.r, color_hovered.g, color_hovered.b, color_hovered.a);
			break;
		case Status::Pushed:
			SDL_SetRenderDrawColor(renderer, color_pushed.r, color_pushed.g, color_pushed.b, color_pushed.a);
			break;
		}
		SDL_RenderFillRect(renderer, &rect_button);
		SDL_SetRenderDrawColor(renderer, color_frame.r, color_frame.g, color_frame.b, color_frame.a);
		SDL_RenderDrawRect(renderer, &rect_button);

		if (have_message)
			SDL_RenderCopy(renderer, texture_message, nullptr, &rect_message);
	}
	else
	{
		switch (status)
		{
		case Status::Idle:
			SDL_RenderCopy(renderer, texture_idle, nullptr, &rect_button);
			break;
		case Status::Hovered:
			SDL_RenderCopy(renderer, texture_hovered, nullptr, &rect_button);
			break;
		case Status::Pushed:
			SDL_RenderCopy(renderer, texture_pushed, nullptr, &rect_button);
			break;
		}
		if (have_message)
			SDL_RenderCopy(renderer, texture_message, nullptr, &rect_message);
	}

}

void Button::on_input(const SDL_Event& event)
{
	if (on_hold)
		return;

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		if (status == Status::Idle && check_cursor_hit(event.motion.x, event.motion.y))
			status = Status::Hovered;
		else if (status == Status::Hovered && !check_cursor_hit(event.motion.x, event.motion.y))
			status = Status::Idle;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (check_cursor_hit(event.button.x, event.button.y))
			{
				status = Status::Pushed;
				if (have_sound_effect_down)
					Mix_PlayChannel(-1, sound_effect_down, 0);
			}
		}
		break;

	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (status == Status::Pushed)
			{
				time_on_click++;
				status = Status::Idle;
				if (have_sound_effect_up)
					Mix_PlayChannel(-1, sound_effect_up, 0);

				if (check_cursor_hit(event.button.x, event.button.y))
				{
					if (on_click)
						on_click();
				}
			}
		}
		break;

	default:
		break;
	}
}

bool Button::check_cursor_hit(int x, int y)const
{
	return x >= rect_button.x && x < (rect_button.x + rect_button.w) &&
		y >= rect_button.y && y < (rect_button.y + rect_button.h);
}

void Button::set_on_click(std::function<void()> func)
{
	on_click = std::move(func);
}

Button::Status Button::get_status()const
{
	return status;
}

void Button::set_status(Status set_status)
{
	status = set_status;
}

void Button::change_rect_button(SDL_Rect new_rect_button)
{
	rect_button = new_rect_button;
}

void Button::change_rect_message(SDL_Rect new_rect_message)
{
	rect_message = new_rect_message;
}

void Button::change_texture_message(SDL_Texture* new_texture_message)
{
	texture_message = new_texture_message;
}

void Button::set_on_holed()
{
	on_hold = true;
}

void Button::reset_on_holed()
{
	on_hold = false;
}

int Button::get_time_on_click()const
{
	return time_on_click;
}

bool Button::check_on_holed()const
{
	return on_hold;
}