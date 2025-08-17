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
	void set_on_fire(std::function<void()> func);
	void set_on_arrive(std::function<void()> func);

protected:
	BulletManager() {};
	~BulletManager() {};

private:
	std::function<void()> on_arrive = nullptr;
	std::function<void()> on_fire = nullptr;

	std::vector<std::unique_ptr<Bullet>> bullet_list;
};