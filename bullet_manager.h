#pragma once
#include"SDL.h"
#include"manager.h"
#include"bullet.h"
#include"skill_type.h"
#include<vector>
#include<memory>
#include<functional>

enum class BulletType
{
	Missile
};

class Board;

class BulletManager :public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	void fire(SDL_Point bullet_start, SDL_Point bullet_end, Board* effect_board, SDL_Point index);
	void fire(SDL_Point bullet_end, Board* effect_board, SDL_Point index);
	void fire(SDL_Point bullet_end, Board* effect_board, SDL_Point index, SkillType skill);

	void on_fire(std::unique_ptr<Bullet>& bullet);
	void on_arrive(std::unique_ptr<Bullet>& bullet);
	void focus_fire(SDL_Point bullet_end, Board* effect_board, SDL_Point index, SkillType skill);

protected:
	BulletManager() {};
	~BulletManager() {};

private:

	std::vector<std::unique_ptr<Bullet>> bullet_list;
};