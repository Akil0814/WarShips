#include"bullet.h"

Bullet::Bullet() {
    animation.set_frame(AtlasManager::instance()->get_atlas(AtlasID::MissileOnFire));
    animation.set_interval(0.1);
    animation.set_loop(true);
}

Bullet::~Bullet() {}

void Bullet::fire(const SDL_Point& start, const SDL_Point& end, double spd)
{
    fx = static_cast<double>(start.x);
    fy = static_cast<double>(start.y);
    end_x = static_cast<double>(end.x);
    end_y = static_cast<double>(end.y);

    double dx = end_x - fx;
    double dy = end_y - fy;
    double len = std::hypot(dx, dy);
    if (len > 0.0) {
        dirX = dx / len;
        dirY = dy / len;
    }
    else {
        dirX = dirY = 0.0;
    }
    // 将弧度转为度用于渲染旋转
    angle_rot = std::atan2(dy, dx) * 180.0 / 3.14159265358979323846;

    speed = spd;
    valid = true;
}

void Bullet::on_update(double delta)
{
    if (valid)
    {
        fx += dirX * speed * delta;
        fy += dirY * speed * delta;

        double toEndX = end_x - fx;
        double toEndY = end_y - fy;
        if ((toEndX * dirX + toEndY * dirY) <= 0.0)
        {
            valid = false;
        }
    }

    animation.on_update(delta);
}

void Bullet::on_render(SDL_Renderer* renderer) const
{
    if (valid)
    {
        SDL_Point pt{
        static_cast<int>(fx - size_x / 2),
        static_cast<int>(fy - size_y / 2)
        };
        animation.on_render(renderer, pt, angle_rot);
    }

}

bool Bullet::is_valid() const {
    return valid;
}
