#pragma once
#include <SDL.h>
#include <cmath>
#include "animation.h"
#include "atlas_manager.h"
#include"resources_manager.h"

class Board;

class Bullet {
public:
    Bullet();
    ~Bullet();

    // 发射子弹: start 起点, end 终点, spd 速度 (px/s)
    void fire(const SDL_Point& start, const SDL_Point& end, double spd, Board* board, SDL_Point index);

    void on_update(double delta);

    void on_render(SDL_Renderer* renderer) const;

    void on_arrive();

    bool is_valid() const;
    SDL_Point get_end_pos()const;

private:
    Animation animation;
    Board* effect_board;
    SDL_Point effect_index;
    SDL_Point end_pos;

    double fx = 0.0, fy = 0.0;      // 浮点位置
    double dirX = 0.0, dirY = 0.0;  // 单位方向向量
    double end_x = 0.0, end_y = 0.0;

    double speed = 0.0;             // 速度(px/s)
    bool valid = false;             // 有效标志
    double angle_rot = 0.0;         // 角度(度)
    int size_x = 58, size_y = 21;   // 子弹纹理尺寸
};

