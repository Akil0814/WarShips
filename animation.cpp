#include"animation.h"

Animation::Animation()
{
	timer.set_one_shot(false);
	timer.set_on_timeout(
		[this]()
		{
			idx_frame++;
			if (idx_frame >= texture_list->get_size())
			{
				idx_frame = is_loop ? 0 : texture_list->get_size() - 1;
                if (!is_loop && on_finished)
                {
                    on_finished();
                    is_finish = true;
                }
			}
		}
	);
}

void Animation::set_frame(const Atlas* atlas)
{
	texture_list = atlas;
}

void Animation::reset()
{
	timer.restart();

	idx_frame = 0;
}

void Animation::set_loop(bool is_loop)
{
	this->is_loop = is_loop;
}

void Animation::set_interval(double interval)
{
    this->interval = interval;
	timer.set_wait_time(interval);
}

void Animation::set_on_finished(PlayCallback on_finished)
{
	this->on_finished = on_finished;
}

void Animation::on_update(double delta)
{
	timer.on_update(delta);
}

void Animation::on_render(SDL_Renderer* renderer, SDL_Rect& rect, double angle = 0) const
{

	SDL_Texture* tex = texture_list->get_texture(idx_frame);
	if (!tex)
		return;

	SDL_Point center;
	center.x = rect.w / 2;
	center.y = rect.h / 2;

	SDL_RenderCopyEx(renderer,tex,nullptr,&rect,angle,&center,SDL_FLIP_NONE);
}

void Animation::on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const
{
    SDL_Texture* tex = texture_list->get_texture(idx_frame);
    if (!tex) 
        return;

    int w, h;
    if (SDL_QueryTexture(tex, nullptr, nullptr, &w, &h) != 0)
        return;

    SDL_Rect dst;
    dst.x = pos_dst.x;
    dst.y = pos_dst.y;
    dst.w = w;
    dst.h = h;

    SDL_Point center{ w / 2, h / 2 };

	SDL_RenderCopyEx(renderer, tex, nullptr, &dst, angle, &center, SDL_FLIP_NONE);
}

void Animation::pause()
{
    timer.pause();
}

void Animation::resume()
{
    timer.resume();
}

bool Animation::is_finished() const
{
    return is_finish;
}
