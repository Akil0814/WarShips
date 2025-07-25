#include "effect.h"

Effect::Effect()
{
	this->is_loop = false;
}

//�����Ч�����Ƿ����
bool Effect::is_finished()
{
	return Animation::is_finished();
}

//������Ч����
void Effect::on_update(double delta)
{
	if(idx_frame==0 && have_sound)
		Mix_PlayChannel(-1, sound_effect, 0);

	Animation::on_update(delta);
}

//��Ⱦ��Ч����
void Effect::on_render(SDL_Renderer* renderer)
{
	if (have_rect)
		Animation::on_render(renderer, play_rect, angle);
	else
		Animation::on_render(renderer,play_pos,angle);
}

//��¡�ӿ�
std::unique_ptr<Effect> Effect::clone()const
{
	auto clone_effect = std::make_unique<Effect>();

	clone_effect->set_frame(texture_list);
	clone_effect->set_interval(interval);
	clone_effect->set_loop(is_loop);
	clone_effect->set_on_finished(on_finished);

	if (have_sound)
		clone_effect->set_sound_effect(sound_effect);

	return clone_effect;
}

//������Ч������Ϣ
void Effect::set_play_data(SDL_Point pos,double angle)
{
	play_pos = pos;
	this->angle = angle;
	have_rect = false;
	is_valid = true;
	Animation::reset();
	is_finish = false;
}

//������Ч������Ϣ
void Effect::set_play_data(SDL_Rect rect, double angel)
{
	play_rect = rect;
	this->angle = angle;
	have_rect = true;
	is_valid = true;
	Animation::reset();
	is_finish = false;
}

//������Ч������Ч
void  Effect::set_sound_effect(Mix_Chunk* sound)
{
	if (sound)
	{
		have_sound = true;
		this->sound_effect = sound;
	}
}
