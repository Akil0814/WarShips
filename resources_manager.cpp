#include"resources_manager.h"

#include<iostream>

bool ResourcesManager::load_from_file(SDL_Renderer* renderer)
{
	//---------------------------------------------------------------//
	//--------------------------字体资源------------------------------//

	font_pool[ResID::Font_48] = TTF_OpenFont("res/Gastroe.otf", 48);
	font_pool[ResID::Font_72] = TTF_OpenFont("res/Gastroe.otf", 72);
	font_pool[ResID::Font_128] = TTF_OpenFont("res/Gastroe.otf", 128);
	font_pool[ResID::Font_256] = TTF_OpenFont("res/Gastroe.otf", 256);
	font_pool[ResID::Font_512] = TTF_OpenFont("res/Gastroe.otf", 512);

	std::cout << "font check" << std::endl;
	for (const auto& pair : font_pool)
		if (!pair.second)return false;
	std::cout << "font good" << std::endl;

	//---------------------------------------------------------------//
	//--------------------------纹理资源------------------------------//

	texture_pool[ResID::Tex_Num_0] = IMG_LoadTexture(renderer, "res/Num/num0.png");
	texture_pool[ResID::Tex_Num_1] = IMG_LoadTexture(renderer, "res/Num/num1.png");
	texture_pool[ResID::Tex_Num_2] = IMG_LoadTexture(renderer, "res/Num/num2.png");
	texture_pool[ResID::Tex_Num_3] = IMG_LoadTexture(renderer, "res/Num/num3.png");
	texture_pool[ResID::Tex_Num_4] = IMG_LoadTexture(renderer, "res/Num/num4.png");
	texture_pool[ResID::Tex_Num_5] = IMG_LoadTexture(renderer, "res/Num/num5.png");
	texture_pool[ResID::Tex_Num_6] = IMG_LoadTexture(renderer, "res/Num/num6.png");
	texture_pool[ResID::Tex_Num_7] = IMG_LoadTexture(renderer, "res/Num/num7.png");
	texture_pool[ResID::Tex_Num_8] = IMG_LoadTexture(renderer, "res/Num/num8.png");
	texture_pool[ResID::Tex_Num_9] = IMG_LoadTexture(renderer, "res/Num/num9.png");

	texture_pool[ResID::Tex_Coin] = IMG_LoadTexture(renderer, "res/UI/coin.png");


	texture_pool[ResID::Tex_SetTarget] = IMG_LoadTexture(renderer, "res/set_target.png");
	texture_pool[ResID::Tex_Hand] = IMG_LoadTexture(renderer, "res/hand.png");

	texture_pool[ResID::Tex_Test_Ship_detel] = IMG_LoadTexture(renderer, "res/Ship/test_d.png");
	texture_pool[ResID::Tex_Ship_Destroyer] = IMG_LoadTexture(renderer, "res/Ship/Destroyer.png");
	texture_pool[ResID::Tex_Ship_LightCruiser] = IMG_LoadTexture(renderer, "res/Ship/LightCruiser.png");
	texture_pool[ResID::Tex_Ship_HeavyCruiser] = IMG_LoadTexture(renderer, "res/Ship/HeavyCruiser.png");
	texture_pool[ResID::Tex_Ship_SuperCruiser] = IMG_LoadTexture(renderer, "res/Ship/SuperCruiser.png");
	texture_pool[ResID::Tex_Ship_BattleCruiser] = IMG_LoadTexture(renderer, "res/Ship/BattleCruiser.png");
	texture_pool[ResID::Tex_Ship_Battleship] = IMG_LoadTexture(renderer, "res/Ship/Battleship.png");
	texture_pool[ResID::Tex_Ship_AviationBattleship] = IMG_LoadTexture(renderer, "res/Ship/AviationBattleship.png");
	texture_pool[ResID::Tex_Ship_AircraftCarrier] = IMG_LoadTexture(renderer, "res/Ship/AircraftCarrier.png");
	texture_pool[ResID::Tex_Ship_LightCarrier] = IMG_LoadTexture(renderer, "res/Ship/LightCarrier.png");
	texture_pool[ResID::Tex_Ship_Submarine] = IMG_LoadTexture(renderer, "res/Ship/Submarine.png");
	texture_pool[ResID::Tex_Ship_RepairShip] = IMG_LoadTexture(renderer, "res/Ship/RepairShip.png");

	//texture_pool[ResID::Tex_ExCalibur_0001] = IMG_LoadTexture(renderer, "res/ExCalibur/");
	
	texture_pool[ResID::Tex_MissileOnFire_0001] = IMG_LoadTexture(renderer, "res/Missile_on_fire/missile_0001.png");
	texture_pool[ResID::Tex_MissileOnFire_0002] = IMG_LoadTexture(renderer, "res/Missile_on_fire/missile_0002.png");
	texture_pool[ResID::Tex_MissileOnFire_0003] = IMG_LoadTexture(renderer, "res/Missile_on_fire/missile_0003.png");
	
	texture_pool[ResID::Tex_GetTarget_0001] = IMG_LoadTexture(renderer, "res/Get_target/get_target_0001.png");
	texture_pool[ResID::Tex_GetTarget_0002] = IMG_LoadTexture(renderer, "res/Get_target/get_target_0002.png");
	texture_pool[ResID::Tex_GetTarget_0003] = IMG_LoadTexture(renderer, "res/Get_target/get_target_0003.png");
	texture_pool[ResID::Tex_GetTarget_0004] = IMG_LoadTexture(renderer, "res/Get_target/get_target_0004.png");
	texture_pool[ResID::Tex_GetTarget_0005] = IMG_LoadTexture(renderer, "res/Get_target/get_target_0005.png");

	texture_pool[ResID::Tex_WaterSplash_0001] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0001.png");
	texture_pool[ResID::Tex_WaterSplash_0002] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0002.png");
	texture_pool[ResID::Tex_WaterSplash_0003] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0003.png");
	texture_pool[ResID::Tex_WaterSplash_0004] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0004.png");
	texture_pool[ResID::Tex_WaterSplash_0005] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0005.png");
	texture_pool[ResID::Tex_WaterSplash_0006] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0006.png");
	texture_pool[ResID::Tex_WaterSplash_0007] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0007.png");
	texture_pool[ResID::Tex_WaterSplash_0008] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0008.png");
	texture_pool[ResID::Tex_WaterSplash_0009] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0009.png");
	texture_pool[ResID::Tex_WaterSplash_0010] = IMG_LoadTexture(renderer, "res/WaterSplash/missed_0010.png");
	
	texture_pool[ResID::Tex_Explosion1_0001] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0001.png");
	texture_pool[ResID::Tex_Explosion1_0002] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0002.png");
	texture_pool[ResID::Tex_Explosion1_0003] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0003.png");
	texture_pool[ResID::Tex_Explosion1_0004] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0004.png");
	texture_pool[ResID::Tex_Explosion1_0005] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0005.png");
	texture_pool[ResID::Tex_Explosion1_0006] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0006.png");
	texture_pool[ResID::Tex_Explosion1_0007] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0007.png");
	texture_pool[ResID::Tex_Explosion1_0008] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0008.png");
	texture_pool[ResID::Tex_Explosion1_0009] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0009.png");
	texture_pool[ResID::Tex_Explosion1_0010] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0010.png");
	texture_pool[ResID::Tex_Explosion1_0011] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0011.png");
	texture_pool[ResID::Tex_Explosion1_0012] = IMG_LoadTexture(renderer, "res/Explosion_1/explosion_big_0012.png");
	
	texture_pool[ResID::Tex_Explosion2_0001] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0001.png");
	texture_pool[ResID::Tex_Explosion2_0002] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0002.png");
	texture_pool[ResID::Tex_Explosion2_0003] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0003.png");
	texture_pool[ResID::Tex_Explosion2_0004] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0004.png");
	texture_pool[ResID::Tex_Explosion2_0005] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0005.png");
	texture_pool[ResID::Tex_Explosion2_0006] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0006.png");
	texture_pool[ResID::Tex_Explosion2_0007] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0007.png");
	texture_pool[ResID::Tex_Explosion2_0008] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0008.png");
	texture_pool[ResID::Tex_Explosion2_0009] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0009.png");
	texture_pool[ResID::Tex_Explosion2_0010] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0010.png");
	texture_pool[ResID::Tex_Explosion2_0011] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0011.png");
	texture_pool[ResID::Tex_Explosion2_0012] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0012.png");
	texture_pool[ResID::Tex_Explosion2_0013] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0013.png");
	texture_pool[ResID::Tex_Explosion2_0014] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0014.png");
	texture_pool[ResID::Tex_Explosion2_0015] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0015.png");
	texture_pool[ResID::Tex_Explosion2_0016] = IMG_LoadTexture(renderer, "res/Explosion_2/explosion_0016.png");

	std::cout << "text check" << std::endl;

	for (const auto& pair : texture_pool)
		if (!pair.second) return false;

	std::cout << "text good" << std::endl;

//---------------------------------------------------------------//
//--------------------------音效资源------------------------------//

	sound_pool[ResID::Sound_Fire_1] = Mix_LoadWAV("res/Sound/fire_1.wav");
	sound_pool[ResID::Sound_Fire_2] = Mix_LoadWAV("res/Sound/fire_2.wav");
	sound_pool[ResID::Sound_Fire_3] = Mix_LoadWAV("res/Sound/fire_3.wav");

	std::cout << "sound check" << std::endl;

	for (const auto& pair : sound_pool)
		if (!pair.second) return false;
	std::cout << "sound good" << std::endl;

//---------------------------------------------------------------//
//--------------------------音乐资源------------------------------//

	//music_pool[ResID::Music_main] = Mix_LoadMUS("");

	std::cout << "music check" << std::endl;

	for (const auto& pair : music_pool)
		if (!pair.second) return false;
	std::cout << "music good" << std::endl;


	return true;
}

TTF_Font* ResourcesManager::get_font(ResID id) const
{
	auto it = font_pool.find(id);

	if (it == font_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font ID %d not loaded", int(id));
		return nullptr;
	}
	return it->second;
}

Mix_Chunk* ResourcesManager::get_sound(ResID id) const
{
	auto it = sound_pool.find(id);

	if (it == sound_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Sound ID %d not loaded", int(id));
		return nullptr;
	}
	return it->second;
}

Mix_Music* ResourcesManager::get_music(ResID id) const
{
	auto it = music_pool.find(id);

	if (it == music_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Music ID %d not loaded", int(id));
		return nullptr;
	}
	return it->second;
}

SDL_Texture* ResourcesManager::get_texture(ResID id)const
{
	auto it = texture_pool.find(id);

	if (it == texture_pool.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture ID %d not loaded", int(id));
		return nullptr;
	}
	return it->second;
}