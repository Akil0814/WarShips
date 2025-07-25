#pragma once
#define SIZE_TILE 50
#include<SDL.h>

class Tile {
public:
    enum class Status { Unknown, Miss, Hit};

    Tile() = default;

    Status get_status() const
    {
        return status;
    }

    void change_status(Status status)
    {
        this->status = status;
    }

    bool has_ship()const
    {
        return have_ship;
    }

    void place_ship()
    {
        have_ship = true;
    }

    void move_ship()
    {
        have_ship = false;
    }

    void mark_miss()
    {
        if (status == Status::Unknown)
            status = Status::Miss;
    }

    void mark_hit()
    {
        if (status == Status::Unknown && have_ship)
            status = Status::Hit;
    }

    SDL_Rect* get_rect()
    {
        return &tile_rect;
    }

private:
    SDL_Rect tile_rect = { 0,0,50,50 };

    Status status = Status::Unknown;
    bool   have_ship = false;
};