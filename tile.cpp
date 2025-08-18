#include"tile.h"
#include "ship.h"

Tile::Status Tile::get_status() const
{
    return status;
}

void Tile::change_status(Status status)
{
    this->status = status;
}

bool Tile::has_ship()const
{
    return ship_on_tile;
}

void Tile::place_ship(Ship* ship)
{
    ship_on_tile = ship;
}

void Tile::move_ship()
{
    ship_on_tile = nullptr;
}

void Tile::take_hit()
{
    if (status == Status::Hit)//ͬһ��Ŀ��λ�ò��ᷴ���ܵ����
        return;

    if (ship_on_tile == nullptr)
        return;

    if (ship_on_tile->can_defense()&& status != Status::Defend)//ÿһ��Ŀ��λ��ֻ�ܷ���һ��
        status = Status::Defend;
    else
        status = Status::Hit;

    ship_on_tile->take_damage();

}
