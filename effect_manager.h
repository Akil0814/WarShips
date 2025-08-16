#pragma once
#include"manager.h"
#include"animation.h"
#include"resources_manager.h"
#include"atlas_manager.h"
#include"effect.h"
#include<SDL.h>
#include<vector>
#include<unordered_map>
#include<functional>

enum class EffectID
{
	SelectTarget,
	WaterSplash,
	WaterSplashMultiple,
	Explosion1,
	Explosion2,
	ExplosionMax,
};

typedef std::unordered_map<EffectID, Effect*> EffectPool;
typedef std::vector<std::unique_ptr<Effect>> EffectOnPlay;

class EffectManager:public Manager<EffectManager>
{
	friend class Manager<EffectManager>;
public:

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	bool init_all_effect();

	void show_effect(EffectID effect_type,const SDL_Point postion, double angle);
	void show_effect(EffectID effect_type, const SDL_Point postion, double angle, std::function<void()>);
	void show_effect(EffectID effect_type,const SDL_Rect rect, double angle);
	void show_effect(EffectID effect_type, const SDL_Rect rect, double angle,std::function<void()>);



	void set_on_finished(EffectID effect_type,std::function<void()>);


protected:
	EffectManager();
	~EffectManager();
private:
	EffectOnPlay effect_on_play;
	EffectPool effect_pool;
};
