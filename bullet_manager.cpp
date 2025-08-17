#include"bullet_manager.h"

void BulletManager :: on_update(double delta)
{
	for (auto& iter : bullet_list)
	{
		iter->on_update(delta);
		if (!(iter->is_valid())&&on_fire)
		{
			on_fire;
		}
	}

	bullet_list.erase(
		std::remove_if(bullet_list.begin(), bullet_list.end(),
			[](const std::unique_ptr<Bullet>& e) { return !e->is_valid(); }),
		bullet_list.end());
}
void  BulletManager::on_render(SDL_Renderer* renderer)
{
	for (auto &iter : bullet_list)
	{
		iter->on_render(renderer);
	}
}

void  BulletManager::fire(SDL_Point start, SDL_Point end)
{
	auto b = std::make_unique<Bullet>();
	b->fire(start, end, 400);
	bullet_list.push_back(std::move(b));
	if (on_fire)
		on_fire;
}

void BulletManager::set_on_fire(std::function<void()> func)
{
	on_fire = func;
}

void BulletManager::set_on_arrive(std::function<void()> func)
{
	on_arrive = func;
}
 