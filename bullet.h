#pragma once

#include <SDL.h>
#include <cmath>
#include "animation.h"
#include "atlas_manager.h"

class Bullet {
public:
    Bullet();
    ~Bullet();

    // 发射子弹: start 起点, end 终点, spd 速度 (px/s)
    void fire(const SDL_Point& start, const SDL_Point& end, double spd);

    // 更新子弹位置和动画
    void on_update(double delta);

    // 渲染子弹到屏幕
    void on_render(SDL_Renderer* renderer) const;

    // 返回子弹是否有效
    bool is_valid() const;

private:
    Animation animation;

    double fx = 0.0, fy = 0.0;      // 浮点位置
    double dirX = 0.0, dirY = 0.0;  // 单位方向向量
    double end_x = 0.0, end_y = 0.0;

    double speed = 0.0;             // 速度(px/s)
    bool valid = false;             // 有效标志
    double angle_rot = 0.0;         // 角度(度)
    int size_x = 58, size_y = 21;   // 子弹纹理尺寸
};

