#pragma once

#include <SDL.h>
#include <cmath>
#include "animation.h"
#include "atlas_manager.h"

class Bullet {
public:
    Bullet();
    ~Bullet();

    // �����ӵ�: start ���, end �յ�, spd �ٶ� (px/s)
    void fire(const SDL_Point& start, const SDL_Point& end, double spd);

    // �����ӵ�λ�úͶ���
    void on_update(double delta);

    // ��Ⱦ�ӵ�����Ļ
    void on_render(SDL_Renderer* renderer) const;

    // �����ӵ��Ƿ���Ч
    bool is_valid() const;

private:
    Animation animation;

    double fx = 0.0, fy = 0.0;      // ����λ��
    double dirX = 0.0, dirY = 0.0;  // ��λ��������
    double end_x = 0.0, end_y = 0.0;

    double speed = 0.0;             // �ٶ�(px/s)
    bool valid = false;             // ��Ч��־
    double angle_rot = 0.0;         // �Ƕ�(��)
    int size_x = 78, size_y = 28;   // �ӵ�����ߴ�
};

