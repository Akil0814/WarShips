#pragma once
#define SIZE_TILE 30
#include<SDL.h>
#include"effect_manager.h"

class Ship;

class Tile {
public:
    enum class Status { Unknown, Miss, Hit, Defend, Detected,Sink };

    Tile() = default;

    Status get_status() const;

    void change_status(Status status);

    bool has_ship()const;

    void place_ship(Ship* sihp);

    void move_ship();

    void take_hit();

    bool can_defense();

private:

    Status status = Status::Unknown;

    Ship* ship_on_tile = nullptr;


};