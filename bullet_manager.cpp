#include"bullet_manager.h"
#include"board.h"


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

void  BulletManager::fire(SDL_Point bullet_start, SDL_Point bullet_end,Board* effect_board,SDL_Point index)
{
	auto b = std::make_unique<Bullet>();
	b->fire(bullet_start, bullet_end, 600,effect_board,index);
	bullet_list.push_back(std::move(b));
	switch (rand() % 3)
	{
	case 0:
		Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Fire_1), 0);
		break;
	case 1:
		Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Fire_2), 0);

		break;
	case 2:
		Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Fire_3), 0);
		break;
	}

}



void BulletManager::on_fire(std::unique_ptr<Bullet>& bullet)
{

}

void BulletManager::on_arrive(std::unique_ptr<Bullet>& bullet)
{
	SDL_Point pos=bullet->get_end_pos();
}
 