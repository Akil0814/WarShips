#include"atlas_manager.h"

AtlasManager::AtlasManager() = default;

AtlasManager::~AtlasManager() = default;

bool AtlasManager::load_atlas()
{
	Atlas* atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_Missile_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_Missile_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_Missile_0003) }))
		return false;
	atlas_pool[AtlasID::Missile] = atlas;

	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0005)}))
		return false;
	atlas_pool[AtlasID::GetTarget] = atlas;


	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0005),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0006),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0007),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0008),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0009),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissTarget0010) }))
		return false;
	atlas_pool[AtlasID::MissingTarget] = atlas;

	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0005),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0006),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0007),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0008),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0009),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0010),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0011),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0012),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0013),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0014),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0015),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_0016) }))
		return false;
	atlas_pool[AtlasID::Explosion] = atlas;


	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0005),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0006),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0007),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0008),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0009),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0010),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0011),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion_big_0012) }))
		return false;
	atlas_pool[AtlasID::ExplosionBig] = atlas;


		did_load_atlas = true;
	return true;
}

Atlas* AtlasManager::get_atlas(AtlasID id) const
{
	if (!did_load_atlas)
		return nullptr;

	auto it = atlas_pool.find(id);

	if (it == atlas_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Atlas ID %d not loaded", int(id));
		return nullptr;
	}
	return it->second;

}