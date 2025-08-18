#include"bullet_manager.h"

void BulletManager :: on_update(double delta)
{
	for (auto& iter : bullet_list)
	{
		iter->on_update(delta);
		if (!iter->is_valid())
		{
			on_arrive(iter);
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
	b->fire(start, end, 600);
	bullet_list.push_back(std::move(b));
}



void BulletManager::on_fire(std::unique_ptr<Bullet>& bullet)
{

}

void BulletManager::on_arrive(std::unique_ptr<Bullet>& bullet)
{
	SDL_Point pos=bullet->get_end_pos();
}
 