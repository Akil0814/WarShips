#pragma once
#include"manager.h"
#include"atlas.h"
#include"resources_manager.h"
#include<unordered_map>

enum class AtlasID
{
	Missile,
	GetTarget,
	MissingTarget,
	Explosion,
	ExplosionBig,

};

typedef std::unordered_map<AtlasID, Atlas*>AtlasPool;

class AtlasManager:public Manager<AtlasManager>
{
	friend class Manager<AtlasManager>;

protected:

	AtlasManager();
	~AtlasManager();

public:

	bool load_atlas();
	Atlas* get_atlas(AtlasID id) const;

private:

	bool did_load_atlas = false;
	AtlasPool atlas_pool;
};

