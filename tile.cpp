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
    if (status == Status::Hit)//同一个目标位置不会反复受到打击
        return;

    if (ship_on_tile == nullptr)
        return;

    if (ship_on_tile->can_defense()&& status != Status::Defend)//每一个目标位置只能防御一次
        status = Status::Defend;
    else
        status = Status::Hit;

    ship_on_tile->take_damage();

}
