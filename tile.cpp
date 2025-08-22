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
    if (status == Status::Hit)
    {
        std::cout << "is hit befor on same tile"<<std::endl;
        return;
    }  

    if (ship_on_tile == nullptr)
    {
        std::cout << "no ship on tile" << std::endl;
        return;
    }

    if (ship_on_tile->can_defense() && status != Status::Defend)//每一个目标位置只能防御一次
    {
        status = Status::Defend;
        std::cout << "change tile to defend" << std::endl;

    }
    else
    {
        status = Status::Hit;
        std::cout << "change tile to hit" << std::endl;

    }
    ship_on_tile->take_damage();

}
