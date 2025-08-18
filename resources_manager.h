#pragma once
#include"manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

enum class ResID
{
//---------------------------------------------------------------//
//--------------------------字体资源------------------------------//
	Font_48,
	Font_72,
	Font_128,
	Font_256,
	Font_512,

//---------------------------------------------------------------//
//--------------------------音效资源------------------------------//
	Sound_Coin,
	Sound_Click,
	Sound_Click_Down,
	Sound_Click_Up,

	Sound_Button_Metal,
	Sound_Error,
	Sound_Put_In_Water,
	Sound_Entering_Water,


	Sound_Fire_1,
	Sound_Fire_2,
	Sound_Fire_3,
	Sound_Fire_4,


//---------------------------------------------------------------//
//--------------------------音乐资源------------------------------//
	Music_Game_End,
	Music_In_Game,
	Music_Setup,

//---------------------------------------------------------------//
//--------------------------纹理资源------------------------------//

	Tex_Num_0,
	Tex_Num_1,
	Tex_Num_2,
	Tex_Num_3,
	Tex_Num_4,
	Tex_Num_5,
	Tex_Num_6,
	Tex_Num_7,
	Tex_Num_8,
	Tex_Num_9,

	Tex_Coin,
	Tex_Atk_Time,
	Tex_Range,
	Tex_Bombs,

	Tex_SetTarget,
	Tex_Hand,

	//棋盘贴图
	Tex_Tile_hit,
	Tex_Tile_miss,
	Tex_Tile_unknow,
	Tex_Tile_defance,
	Tex_Tile_sink,



	//舰船贴图
	Tex_Test_Ship_detel,/////////////////////////////////////////////////////////


	Tex_Ship_Infrom_Destroyer,//驱逐
	Tex_Ship_Infrom_LightCruiser,//轻巡
	Tex_Ship_Infrom_HeavyCruiser,//重巡
	Tex_Ship_Infrom_SuperCruiser,//超巡
	Tex_Ship_Infrom_BattleCruiser,//战巡
	Tex_Ship_Infrom_Battleship,//战列
	Tex_Ship_Infrom_AviationBattleship,//航战
	Tex_Ship_Infrom_AircraftCarrier,//航母
	Tex_Ship_Infrom_LightCarrier,//轻航
	Tex_Ship_Infrom_Submarine,//潜艇
	Tex_Ship_Infrom_RepairShip,//维修


	Tex_Ship_Destroyer,//驱逐
	Tex_Ship_LightCruiser,//轻巡
	Tex_Ship_HeavyCruiser,//重巡
	Tex_Ship_SuperCruiser,//超巡
	Tex_Ship_BattleCruiser,//战巡
	Tex_Ship_Battleship,//战列
	Tex_Ship_AviationBattleship,//航战
	Tex_Ship_AircraftCarrier,//航母
	Tex_Ship_LightCarrier,//轻航
	Tex_Ship_Submarine,//潜艇
	Tex_Ship_RepairShip,//维修

////--------------动画特效类资源----------------////
	//特殊宝具动画
	Tex_ExCalibur_0001,
	Tex_ExCalibur_0002,
	Tex_ExCalibur_0003,
	Tex_ExCalibur_0004,
	Tex_ExCalibur_0005,
	Tex_ExCalibur_0006,

	//爆炸特效1
	Tex_Explosion1_0001,
	Tex_Explosion1_0002,
	Tex_Explosion1_0003,
	Tex_Explosion1_0004,
	Tex_Explosion1_0005,
	Tex_Explosion1_0006,
	Tex_Explosion1_0007,
	Tex_Explosion1_0008,
	Tex_Explosion1_0009,
	Tex_Explosion1_0010,
	Tex_Explosion1_0011,
	Tex_Explosion1_0012,

	//爆炸特效2
	Tex_Explosion2_0001,
	Tex_Explosion2_0002,
	Tex_Explosion2_0003,
	Tex_Explosion2_0004,
	Tex_Explosion2_0005,
	Tex_Explosion2_0006,
	Tex_Explosion2_0007,
	Tex_Explosion2_0008,
	Tex_Explosion2_0009,
	Tex_Explosion2_0010,
	Tex_Explosion2_0011,
	Tex_Explosion2_0012,
	Tex_Explosion2_0013,
	Tex_Explosion2_0014,
	Tex_Explosion2_0015,
	Tex_Explosion2_0016,

	//巨型爆炸特效
	Tex_Explosion_Max_0001,
	Tex_Explosion_Max_0002,
	Tex_Explosion_Max_0003,
	Tex_Explosion_Max_0004,
	Tex_Explosion_Max_0005,
	Tex_Explosion_Max_0006,
	Tex_Explosion_Max_0007,
	Tex_Explosion_Max_0008,
	Tex_Explosion_Max_0009,
	Tex_Explosion_Max_0010,
	Tex_Explosion_Max_0011,
	Tex_Explosion_Max_0012,
	Tex_Explosion_Max_0013,
	Tex_Explosion_Max_0014,
	Tex_Explosion_Max_0015,
	Tex_Explosion_Max_0016,
	Tex_Explosion_Max_0017,
	Tex_Explosion_Max_0018,
	Tex_Explosion_Max_0019,
	Tex_Explosion_Max_0020,
	Tex_Explosion_Max_0021,
	Tex_Explosion_Max_0022,
	Tex_Explosion_Max_0023,
	Tex_Explosion_Max_0024,
	Tex_Explosion_Max_0025,
	Tex_Explosion_Max_0026,
	Tex_Explosion_Max_0027,
	Tex_Explosion_Max_0028,
	Tex_Explosion_Max_0029,
	Tex_Explosion_Max_0030,
	Tex_Explosion_Max_0031,
	Tex_Explosion_Max_0032,
	Tex_Explosion_Max_0033,
	Tex_Explosion_Max_0034,

	//选中目标位置特效
	Tex_GetTarget_0001,
	Tex_GetTarget_0002,
	Tex_GetTarget_0003,
	Tex_GetTarget_0004,
	Tex_GetTarget_0005,

	//导弹飞行动画
	Tex_MissileOnFire_0001,
	Tex_MissileOnFire_0002,
	Tex_MissileOnFire_0003,

	//未命中目标水花特效
	Tex_WaterSplash_0001,
	Tex_WaterSplash_0002,
	Tex_WaterSplash_0003,
	Tex_WaterSplash_0004,
	Tex_WaterSplash_0005,
	Tex_WaterSplash_0006,
	Tex_WaterSplash_0007,
	Tex_WaterSplash_0008,
	Tex_WaterSplash_0009,
	Tex_WaterSplash_0010,

	//未命中目标多个水花特效
	Tex_WaterSplash_Multiple_0001,
	Tex_WaterSplash_Multiple_0002,
	Tex_WaterSplash_Multiple_0003,
	Tex_WaterSplash_Multiple_0004,
	Tex_WaterSplash_Multiple_0005,
	Tex_WaterSplash_Multiple_0006,
};

typedef std::unordered_map<ResID, TTF_Font*> FontPool;
typedef std::unordered_map<ResID, Mix_Chunk*> SoundPool;
typedef std::unordered_map<ResID, Mix_Music*> MusicPool;
typedef std::unordered_map<ResID, SDL_Texture*> TexturePool;

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:

public:

	bool load_from_file(SDL_Renderer* renderer);

	TTF_Font* get_font(ResID id) const;
	Mix_Chunk* get_sound(ResID id) const;
	Mix_Music* get_music(ResID id) const;
	SDL_Texture* get_texture(ResID id)const;

protected:
	ResourcesManager() {};
	~ResourcesManager() {};

private:
	FontPool font_pool;
	SoundPool sound_pool;
	MusicPool music_pool;
	TexturePool texture_pool;
};
