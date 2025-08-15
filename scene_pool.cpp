#include"scene_pool.h"

ScenePool* ScenePool::scene_pool = nullptr;

Scene* ScenePool::get_scene(SceneType type)
{
	switch (type)
	{
	case SceneType::Menu:
		if (cheek_invalid(menu_scene))
			menu_scene = new MenuScene;
		return menu_scene;
		break;

	case SceneType::Setting:
		if (cheek_invalid(setting_scene))
			//setting_scene = new SettingScene;
		return setting_scene;
		break;

	case SceneType::Game:
		if (cheek_invalid(game_scene))
			game_scene = new GameScene;
		return game_scene;
		break;

	case SceneType::Setup:
		if (cheek_invalid(setup_scene))
			setup_scene = new SetupScene;
		return setup_scene;
		break;

	case SceneType::Settlement:
		if (cheek_invalid(settlement_scene))
			settlement_scene = new SettlementScene;
			return settlement_scene;
		break;

	default:
		return nullptr;
		break;
	}

	return nullptr;
}

void ScenePool::delete_scene(SceneType type)
{
	switch (type)
	{
	case SceneType::Menu:

		if (cheek_invalid(menu_scene))
			return;
		delete menu_scene;
		break;

	case SceneType::Setting:

		if (cheek_invalid(setting_scene))
			return;
		delete setting_scene;
		break;

	case SceneType::Game:

		if (cheek_invalid(game_scene))
			return;
		delete  game_scene;
		break;

	case SceneType::Setup:

		if (cheek_invalid(setup_scene))
			return;
		delete setup_scene;
		break;

	case SceneType::Settlement:
		if (cheek_invalid(settlement_scene))
			return;
		delete settlement_scene;
		break;

	default:
		break;
	}
}

bool ScenePool::cheek_invalid(Scene* scene)
{
	if (scene == nullptr)
		return true;

	return false;
}

