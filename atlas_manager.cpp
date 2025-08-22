#include"atlas_manager.h"

AtlasManager::AtlasManager() = default;

AtlasManager::~AtlasManager() = default;

bool AtlasManager::load_atlas()
{
	Atlas* atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_MissileOnFire_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissileOnFire_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_MissileOnFire_0003) }))
		return false;
	atlas_pool[AtlasID::MissileOnFire] = atlas;

	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_GetTarget_0005)}))
		return false;
	atlas_pool[AtlasID::GetTarget] = atlas;


	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0005),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0006),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0007),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0008),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0009),
			ResourcesManager::instance()->get_texture(ResID::Tex_WaterSplash_0010) }))
		return false;
	atlas_pool[AtlasID::WaterSplash] = atlas;


	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0005),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0006),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0007),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0008),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion1_0009), }))
		return false;
	atlas_pool[AtlasID::Explosion1] = atlas;

	atlas = new Atlas;
	if (!atlas->add_Textures({ ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0001),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0002),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0003),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0004),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0005),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0006),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0007),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0008),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0009),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0010),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0011),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0012),
			ResourcesManager::instance()->get_texture(ResID::Tex_Explosion2_0013)}))
		return false;
	atlas_pool[AtlasID::Explosion2] = atlas;

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