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
    return have_ship;
}

void Tile::place_ship(Ship* ship)
{
    ship_on_tile = ship;
    have_ship = true;
}

void Tile::move_ship()
{
    have_ship = false;
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
