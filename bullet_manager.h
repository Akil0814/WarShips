#pragma once
#include"SDL.h"
#include"manager.h"
#include"bullet.h"
#include<vector>
#include<memory>
#include<functional>

enum class BulletType
{
	Missile
};


class BulletManager :public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	void fire(SDL_Point start, SDL_Point end);
	void on_fire(std::unique_ptr<Bullet>& bullet);
	void on_arrive(std::unique_ptr<Bullet>& bullet);

protected:
	BulletManager() {};
	~BulletManager() {};

private:

	std::vector<std::unique_ptr<Bullet>> bullet_list;
};