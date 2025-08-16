#pragma once
#include"SDL.h"
#include"manager.h"
#include"bullet.h"

class BulletManager :public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	void fire(SDL_Point pos);

protected:
	BulletManager() {};
	~BulletManager() {};

private:
};