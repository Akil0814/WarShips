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
	if (!effect_board->is_inside(bullet_end.x, bullet_end.y))
	{
		std::cout << "fire not in board"<<std::endl;
		return;
	}

	auto b = std::make_unique<Bullet>();
	b->fire(bullet_start, bullet_end, 500, effect_board, index);
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

void  BulletManager::fire(SDL_Point bullet_end, Board* effect_board, SDL_Point index)
{
	auto b = std::make_unique<Bullet>();

	int pos_y ,low,high= 0;
	if (bullet_end.y < 230)
		low = 320, high = 620;
	else if (bullet_end.y > 420)
		low = 30, high = 330;
	else
		low = 30, high = 620;

	pos_y = low + std::rand() % (high - low + 1);

	std::cout << "fire at: " << pos_y << std::endl;
	std::cout << "fire to: " << bullet_end.x << "," << bullet_end.y << std::endl;

	SDL_Point bullet_start = { 640,pos_y };
	b->fire(bullet_start, bullet_end, 500, effect_board, index);
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

void  BulletManager::fire(SDL_Point bullet_end, Board* effect_board, SDL_Point index,SkillType skill)
{
	switch (skill)
	{
	case SkillType::NONE:
		return;
		break;
	case SkillType::Missile:
		std::cout << "Missile "<< std::endl;
		fire(bullet_end, effect_board, index);
		break;
	case SkillType::Attack_5C:
		std::cout << "Atk 5c" << std::endl;

		fire({ bullet_end.x,0 }, bullet_end, effect_board, index);//center

		fire({ bullet_end.x,0 }, { bullet_end.x,bullet_end.y - SIZE_TILE }, effect_board, { index.x,index.y - 1 });//up
		fire({ bullet_end.x,0 }, { bullet_end.x,bullet_end.y + SIZE_TILE }, effect_board, { index.x,index.y + 1 });//down
		fire({ bullet_end.x + SIZE_TILE,0 }, { bullet_end.x + SIZE_TILE,bullet_end.y }, effect_board, { index.x + 1,index.y });//right
		fire({ bullet_end.x - SIZE_TILE,0 }, { bullet_end.x - SIZE_TILE,bullet_end.y }, effect_board, { index.x - 1,index.y });//left

		break;
	case SkillType::Attack_3x3:
		std::cout << "Atk 9c" << std::endl;

		fire({ bullet_end.x,0 }, bullet_end, effect_board, index);

		fire({ bullet_end.x,0 }, { bullet_end.x,bullet_end.y - SIZE_TILE }, effect_board, { index.x,index.y - 1 });//up
		fire({ bullet_end.x,0 }, { bullet_end.x,bullet_end.y + SIZE_TILE }, effect_board, { index.x,index.y + 1 });//down
		fire({ bullet_end.x + SIZE_TILE,0 }, { bullet_end.x + SIZE_TILE,bullet_end.y }, effect_board, { index.x + 1,index.y });//right
		fire({ bullet_end.x - SIZE_TILE,0 }, { bullet_end.x - SIZE_TILE,bullet_end.y }, effect_board, { index.x - 1,index.y });//left

		fire({ bullet_end.x + SIZE_TILE,0 }, { bullet_end.x + SIZE_TILE,bullet_end.y - SIZE_TILE }, effect_board, { index.x + 1,index.y - 1 });//up r
		fire({ bullet_end.x - SIZE_TILE,0 }, { bullet_end.x - SIZE_TILE,bullet_end.y - SIZE_TILE }, effect_board, { index.x - 1,index.y - 1 });//up l

		fire({ bullet_end.x + SIZE_TILE,0 }, { bullet_end.x + SIZE_TILE,bullet_end.y + SIZE_TILE }, effect_board, { index.x + 1,index.y + 1 });//down r
		fire({ bullet_end.x - SIZE_TILE,0 }, { bullet_end.x - SIZE_TILE,bullet_end.y + SIZE_TILE }, effect_board, { index.x - 1,index.y + 1 });//down l
		break;
	default:
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
 