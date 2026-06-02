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
    if (ship_on_tile == nullptr ||status == Status::Sink|| status == Status::Hit)
        return;


    if (ship_on_tile->can_defense())
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

bool Tile::can_defense()
{
   return ship_on_tile->can_defense();
}

Ship* Tile::get_ship_on_tile()
{
    return ship_on_tile;

}

void Tile::reinforce_ship()
{
	ship_on_tile->reinforce();
}
