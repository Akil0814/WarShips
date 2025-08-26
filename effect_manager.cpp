#include"effect_manager.h"

EffectManager::EffectManager() = default;

EffectManager::~EffectManager() = default;


//更新处于播放状态的特效,删除播完的特效
void EffectManager::on_update(double delta)
{
	for (auto& effect : effect_on_play)
		effect->on_update(delta);

	auto it = std::remove_if(effect_on_play.begin(), effect_on_play.end(),
		[](auto& e) { return e->is_finished(); });
	effect_on_play.erase(it, effect_on_play.end());
}

//渲染处于播放状态的特效
void EffectManager::on_render(SDL_Renderer* renderer)
{
	for (auto& effect : effect_on_play)
		effect->on_render(renderer);
}

//以渲染矩形的方式渲染
void EffectManager::show_effect(EffectID effect_type, const SDL_Rect rect, double angle)
{
	auto effect_prototype = effect_pool.find(effect_type);

	if (effect_prototype == effect_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Effect ID %d can't found", int(effect_type));
		return;
	}

	std::unique_ptr<Effect> new_effect = effect_prototype->second->clone();
	new_effect->set_play_data(rect, angle);
	effect_on_play.push_back(std::move(new_effect));
}

//以渲染目标点的方式渲染
void EffectManager::show_effect(EffectID effect_type, const SDL_Point pos, double angle)
{
	auto effect_prototype = effect_pool.find(effect_type);

	if (effect_prototype == effect_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Effect ID %d can't found", int(effect_type));
		return;
	}

	std::unique_ptr<Effect> new_effect = effect_prototype->second->clone();
	new_effect->set_play_data(pos, angle);
	effect_on_play.push_back(std::move(new_effect));
}

//给在不同场景 调用的相同特效 设置不同回调
void EffectManager::show_effect(EffectID effect_type,const SDL_Rect rect, double angle,std::function<void()> finished)
{
	auto effect_prototype = effect_pool.find(effect_type);

	if (effect_prototype == effect_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Effect ID %d can't found", int(effect_type));
		return;
	}

	std::unique_ptr<Effect> new_effect = effect_prototype->second->clone();
	new_effect->set_play_data(rect, angle);
	new_effect->set_on_finished(finished);
	effect_on_play.push_back(std::move(new_effect));
}

//给在不同场景 调用的相同特效 设置不同回调
void EffectManager::show_effect(EffectID effect_type, const SDL_Point pos, double angle, std::function<void()> finished)
{
	auto effect_prototype = effect_pool.find(effect_type);

	if (effect_prototype == effect_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Effect ID %d can't found", int(effect_type));
		return;
	}

	std::unique_ptr<Effect> new_effect = effect_prototype->second->clone();
	new_effect->set_play_data(pos, angle);
	new_effect->set_on_finished(finished);
	effect_on_play.push_back(std::move(new_effect));
}

//设置回调函数
void EffectManager::set_on_finished(EffectID effect_type, std::function<void()> finished)
{
	auto effect_prototype = effect_pool.find(effect_type);

	if (effect_prototype == effect_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Effect ID %d can't found", int(effect_type));
		return;
	}

	effect_prototype->second->set_on_finished(finished);
}

//初始化所有特效//
bool EffectManager::init_all_effect()
{

	Effect* e = new Effect;
	e->set_frame(AtlasManager::instance()->get_atlas(AtlasID::GetTarget));
	e->set_interval(0.15);
	e->set_loop(false);
	effect_pool[EffectID::SelectTarget] = e;

	e = new Effect;
	e->set_frame(AtlasManager::instance()->get_atlas(AtlasID::WaterSplash));
	e->set_interval(0.1);
	e->set_loop(false);
	effect_pool[EffectID::WaterSplash] = e;

	e = new Effect;
	e->set_frame(AtlasManager::instance()->get_atlas(AtlasID::Explosion1));
	e->set_interval(0.1);
	e->set_loop(false);
	effect_pool[EffectID::Explosion1] = e;


	e = new Effect;
	e->set_frame(AtlasManager::instance()->get_atlas(AtlasID::Explosion2));
	e->set_interval(0.1);
	e->set_loop(false);
	effect_pool[EffectID::Explosion2] = e;


	e = new Effect;
	e->set_frame(AtlasManager::instance()->get_atlas(AtlasID::Shield));
	e->set_interval(0.1);
	e->set_loop(false);
	effect_pool[EffectID::Shield] = e;


	for (const auto& pair : effect_pool)
	{
		if (!pair.second)
			return false;
	}

	return true;
}