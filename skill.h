#pragma once
#include<SDL.h>

class Skill
{
public:
	Skill();
	~Skill();

private:
	SDL_Texture* icon = nullptr;
	SDL_Point texture_pos = { 0 };
	SDL_Rect texture_rect = { 0 };
};
