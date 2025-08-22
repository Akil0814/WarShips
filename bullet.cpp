#include"bullet.h"
#include "board.h"


Bullet::Bullet() {
    animation.set_frame(AtlasManager::instance()->get_atlas(AtlasID::MissileOnFire));
    animation.set_interval(0.1);
    animation.set_loop(true);
}

Bullet::~Bullet() {}

void Bullet::fire(const SDL_Point& start, const SDL_Point& end, double spd,Board* board, SDL_Point index)
{
    fx = static_cast<double>(start.x);
    fy = static_cast<double>(start.y);
    end_x = static_cast<double>(end.x);
    end_y = static_cast<double>(end.y);
    effect_board = board;
    effect_index = index;
    end_pos = end;

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
            on_arrive();
        }
    }

    animation.on_update(delta);
}

void Bullet::on_render(SDL_Renderer* renderer) const
{
    if (valid)
    {
        SDL_Rect rect{
        static_cast<int>(fx - size_x / 2),
        static_cast<int>(fy - size_y / 2),
        size_x,size_y
        };

        animation.on_render(renderer, rect, angle_rot);
    }

}

bool Bullet::is_valid() const
{
    return valid;
}

SDL_Point Bullet::get_end_pos()const
{
    return { static_cast<int>(end_x),static_cast<int>(end_y) };
}


void Bullet::on_arrive()
{

    Board* board = effect_board;
    SDL_Point index = effect_index;

    if (!board) return;
    if (effect_board->get_tile_board()[effect_index.y][effect_index.x].has_ship())
    {
        SDL_Rect rect_explosion_target = {
        end_pos.x-40,end_pos.y-60,
        SIZE_TILE + 40, SIZE_TILE + 40 };

        //effect_board->show_board(5);

        EffectManager::instance()->show_effect(EffectID::Explosion1, rect_explosion_target, 0, [board,index]()
            {
                board->get_tile_board()[index.y][index.x].take_hit();
            });
    }
    else
    {
        SDL_Rect rect_water_splash = {
        end_pos.x- 40,end_pos.y-20,
        SIZE_TILE + 40, SIZE_TILE
        };

        effect_board->get_tile_board()[effect_index.y][effect_index.x].change_status(Tile::Status::Miss);
        //effect_board->show_board(5);

        EffectManager::instance()->show_effect(EffectID::WaterSplash, rect_water_splash, 0, [board,index]()
            {
                board->get_tile_board()[index.y][index.x].change_status(Tile::Status::Miss);
            });
    }

}
