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

void Tile::mark_miss()
{
    if (status == Status::Unknown)
        status = Status::Miss;
}

void Tile::mark_hit()
{
    if (status == Status::Unknown && have_ship)
        status = Status::Hit;
}
