#pragma once
#include"manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

enum class ResID
{
//---------------------------------------------------------------//
//--------------------------������Դ------------------------------//
	Font_48,
	Font_72,
	Font_128,
	Font_256,
	Font_512,

//---------------------------------------------------------------//
//--------------------------��Ч��Դ------------------------------//
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
//--------------------------������Դ------------------------------//
	Music_Game_End,
	Music_In_Game,
	Music_Setup,

//---------------------------------------------------------------//
//--------------------------������Դ------------------------------//

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

	//������ͼ
	Tex_Tile_hit,
	Tex_Tile_miss,
	Tex_Tile_unknow,
	Tex_Tile_defance,
	Tex_Tile_sink,



	//������ͼ
	Tex_Test_Ship_detel,/////////////////////////////////////////////////////////


	Tex_Ship_Infrom_Destroyer,//����
	Tex_Ship_Infrom_LightCruiser,//��Ѳ
	Tex_Ship_Infrom_HeavyCruiser,//��Ѳ
	Tex_Ship_Infrom_SuperCruiser,//��Ѳ
	Tex_Ship_Infrom_BattleCruiser,//սѲ
	Tex_Ship_Infrom_Battleship,//ս��
	Tex_Ship_Infrom_AviationBattleship,//��ս
	Tex_Ship_Infrom_AircraftCarrier,//��ĸ
	Tex_Ship_Infrom_LightCarrier,//�ẽ
	Tex_Ship_Infrom_Submarine,//Ǳͧ
	Tex_Ship_Infrom_RepairShip,//ά��


	Tex_Ship_Destroyer,//����
	Tex_Ship_LightCruiser,//��Ѳ
	Tex_Ship_HeavyCruiser,//��Ѳ
	Tex_Ship_SuperCruiser,//��Ѳ
	Tex_Ship_BattleCruiser,//սѲ
	Tex_Ship_Battleship,//ս��
	Tex_Ship_AviationBattleship,//��ս
	Tex_Ship_AircraftCarrier,//��ĸ
	Tex_Ship_LightCarrier,//�ẽ
	Tex_Ship_Submarine,//Ǳͧ
	Tex_Ship_RepairShip,//ά��

////--------------������Ч����Դ----------------////
	//���ⱦ�߶���
	Tex_ExCalibur_0001,
	Tex_ExCalibur_0002,
	Tex_ExCalibur_0003,
	Tex_ExCalibur_0004,
	Tex_ExCalibur_0005,
	Tex_ExCalibur_0006,

	//��ը��Ч1
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

	//��ը��Ч2
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

	//���ͱ�ը��Ч
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

	//ѡ��Ŀ��λ����Ч
	Tex_GetTarget_0001,
	Tex_GetTarget_0002,
	Tex_GetTarget_0003,
	Tex_GetTarget_0004,
	Tex_GetTarget_0005,

	//�������ж���
	Tex_MissileOnFire_0001,
	Tex_MissileOnFire_0002,
	Tex_MissileOnFire_0003,

	//δ����Ŀ��ˮ����Ч
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

	//δ����Ŀ����ˮ����Ч
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
