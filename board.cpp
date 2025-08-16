#include "board.h"
#include <cmath>

//特效rect需要多个 加入队列管理

SDL_Texture* Board::tile_hit = nullptr;
SDL_Texture* Board::tile_miss = nullptr;

Board::Board()
{
    board.assign(row, std::vector<Tile>(col));
}

Board::~Board() = default;

void Board::on_render(SDL_Renderer* renderer)
{
    draw_board(renderer);

    EffectManager::instance()->on_render(renderer);

    if(missile!=nullptr)
        missile->on_render(renderer);////////////////

    // 渲染所有格子状态
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x)
        {
            SDL_Rect rect = {
                board_render_x + x * SIZE_TILE,
                board_render_y + y * SIZE_TILE,
                SIZE_TILE, SIZE_TILE};
            switch (board[y][x].get_status())
            {

            }
        }
    }
}

void Board::on_update(double delta)
{
    EffectManager::instance()->on_update(delta);//局内

    if (missile != nullptr)
        missile->on_update(delta);

    if (find_target)
    {
        std::cout << "board find target" << std::endl;
        find_target = false;

        if (board[index_y][index_x].has_ship())
        {
            rect_explosion_target = {
            board_render_x + index_x * SIZE_TILE - 20,
            board_render_y + index_y * SIZE_TILE - 40,
            SIZE_TILE + 40, SIZE_TILE + 40 };

            EffectManager::instance()->show_effect(EffectID::Explosion1, rect_explosion_target, 0, [this]()
            {
                board[index_y][index_x].take_hit();
                finish_hit = true;
            });
        }

        else
        {
            rect_water_splash = {
            board_render_x + index_x * SIZE_TILE - 20,
            board_render_y + index_y * SIZE_TILE,
            SIZE_TILE + 40, SIZE_TILE
            };
            EffectManager::instance()->show_effect(EffectID::WaterSplash, rect_water_splash, 0, [this]()
                {
                    board[index_y][index_x].change_status(Tile::Status::Miss);
                    finish_hit = true;
                });
        }
    }
}

void Board::on_input(const SDL_Event& event)
{
    on_mouse_move(event);
    on_mouse_click(event);
}



void Board::on_mouse_move(const SDL_Event& event)
{
    if (is_inside(event.motion.x, event.motion.y)) {
        move_in_board = true;
        mouse_pos.x = event.motion.x;
        mouse_pos.y = event.motion.y;
    }
    else
    {
        move_in_board = false;
    }
}

void Board::on_mouse_click(const SDL_Event& event)
{
    if (!is_inside(event.button.x, event.button.y))
    {
        click_in_board = false;
        return;
    }

    click_in_board = true;
    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        int x = (event.button.x - board_render_x) / SIZE_TILE;
        int y = (event.button.y - board_render_y) / SIZE_TILE;//计算位置

        if (x < 0 || x >= col || y < 0 || y >= row)
            return;

        index_x = x;
        index_y = y;

        mouse_click_tile_center =
        {
            board_render_x + x * SIZE_TILE + SIZE_TILE / 2,
            board_render_y + y * SIZE_TILE + SIZE_TILE / 2
        };

        rect_select_target = {
            board_render_x + x * SIZE_TILE - 20,
            board_render_y + y * SIZE_TILE - 20,
            SIZE_TILE + 40, SIZE_TILE + 40
        };


        EffectManager::instance()->show_effect(EffectID::SelectTarget, rect_select_target, 0, [this]()
            {
                this->find_target = true;
                missile = new Bullet;
                missile->fire({ 0,0 }, mouse_click_tile_center, 400);
            });
    }
}

bool Board::is_inside(int x, int y) const
{
    return x >= board_render_x
        && x < board_render_x + col * SIZE_TILE
        && y >= board_render_y
        && y < board_render_y + row * SIZE_TILE;
}

void Board::draw_board(SDL_Renderer* renderer)
{
    // 棋盘底色
    SDL_Rect board_rect =
    {
        board_render_x, board_render_y,
        col * SIZE_TILE, row * SIZE_TILE
    };
    SDL_SetRenderDrawColor(renderer, 75,100,133, 255);
    SDL_RenderFillRect(renderer, &board_rect);

    // 网格线
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 30, 63, 102, 255);

    // 竖线
    for (int i = 0; i <= col; ++i) 
    {
        int x = board_render_x + i * SIZE_TILE;
        SDL_RenderDrawLine(
            renderer, x, board_render_y, x,
            board_render_y + row * SIZE_TILE
        );
    }
    // 横线
    for (int j = 0; j <= row; ++j) 
    {
        int y = board_render_y + j * SIZE_TILE;
        SDL_RenderDrawLine(
            renderer, board_render_x, y,
            board_render_x + col * SIZE_TILE, y
        );
    }
}

SDL_Point Board::place_ship(Ship* ship, SDL_Point pos, int ship_size, bool is_horizontal)
{
    int x, y = 0;

    if (pos.x - board_render_x < -(SIZE_TILE / 2) || pos.y - board_render_y < -(SIZE_TILE / 2))
    {
        x = std::floor(double(pos.x - board_render_x) / SIZE_TILE);
        y = std::floor(double(pos.y - board_render_y) / SIZE_TILE);
    }
    else
    {
        x = (pos.x - board_render_x) / SIZE_TILE;
        y = (pos.y - board_render_y) / SIZE_TILE;
    }

    if ((pos.x - board_render_x) % SIZE_TILE > SIZE_TILE / 2)
        x++;

    if ((pos.y - board_render_y) % SIZE_TILE > SIZE_TILE / 2)
        y++;

    if (check_available(x, y, ship_size, is_horizontal))
    {
        if (is_horizontal)
        {
            for (int i = 0; i < ship_size; ++i)
            {
                board[y][x + i].place_ship(ship);
            }
        }
        else
        {
            for (int i = 0; i < ship_size; ++i)
            {
                board[y + i][x].place_ship(ship);
            }
        }
        show_board();
        return { (x * SIZE_TILE) + board_render_x,(y * SIZE_TILE) + board_render_y };
    }
    return { -1,-1 };
}

void Board::move_ship(SDL_Point pos, int ship_size, bool is_horizontal)
{
    if (!is_inside(pos.x, pos.y))
        return;

    int x = (pos.x - board_render_x) / SIZE_TILE;
    int y = (pos.y - board_render_y) / SIZE_TILE;
    std::cout << "remove ship" << std::endl;////////////////////////////////

        if (is_horizontal)
        {
            for (int i = 0; i < ship_size; ++i)
            {
                board[y][x + i].move_ship();
            }
        }
        else
        {
            for (int i = 0; i < ship_size; ++i)
            {
                board[y + i][x].move_ship();
            }
        }
        show_board();
}

bool Board::check_available(int x,int y, int ship_size, bool is_horizontal)
{
    // 基本边界和已有船检测
    if (x < 0 || x >= col || y < 0 || y >= row)
        return false;

    if (board[y][x].has_ship())
        return false;

    if (is_horizontal) {
        if (x + ship_size > col)
            return false;
        for (int i = 1; i < ship_size; ++i)
        {
            if (board[y][x + i].has_ship())
                return false;
        }
    }
    else
    {
        if (y + ship_size > row)
            return false;
        for (int i = 1; i < ship_size; ++i)
        {
            if (board[y + i][x].has_ship())
                return false;
        }
    }
    return true;
}

void Board::show_place_feasibility(SDL_Renderer* renderer, SDL_Point pos, int ship_size, bool is_horizontal)
{
    SDL_Point grid_pos = { 0 };


    if (pos.x - board_render_x < -(SIZE_TILE / 2) || pos.y - board_render_y < -(SIZE_TILE / 2))
    {
        int g_pos_x = std::floor( double(pos.x - board_render_x) / SIZE_TILE);
        int g_pos_y = std::floor(double(pos.y - board_render_y) / SIZE_TILE);

        grid_pos = {g_pos_x,g_pos_y};
    }
    else
    {
        grid_pos =
        {
            (pos.x - board_render_x) / SIZE_TILE,
            (pos.y - board_render_y) / SIZE_TILE
        };
    }

    if ((pos.x - board_render_x) % SIZE_TILE > SIZE_TILE / 2)
        grid_pos.x++;

    if ((pos.y - board_render_y) % SIZE_TILE > SIZE_TILE / 2)
        grid_pos.y++;


    SDL_Rect rect = {
                    board_render_x + grid_pos.x * SIZE_TILE,
                    board_render_y + grid_pos.y * SIZE_TILE,
                    is_horizontal ? ship_size * SIZE_TILE : SIZE_TILE,
                    is_horizontal ? SIZE_TILE : ship_size * SIZE_TILE };


    bool valid = check_available(grid_pos.x, grid_pos.y, ship_size, is_horizontal);

    SDL_SetRenderDrawColor(renderer,valid ? 255 : 255,valid ? 255 : 0,valid ? 255 : 0,50);

    SDL_RenderFillRect(renderer, &rect);
}

void Board::reset_board()
{
    board.assign(row, std::vector<Tile>(col));
}

void Board::set_size(int r, int c)
{
    row = r; col = c;
    board.assign(row, std::vector<Tile>(col));
}

void Board::set_board_pos(SDL_Point pt)
{
    board_render_x = pt.x;
    board_render_y = pt.y;
}

bool Board::finish_hit_time()const
{
    return finish_hit;
}

void Board::reset_hit_time()
{
    finish_hit = false;
}

void Board::draw_cover(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 54);
    SDL_Rect rect = { board_render_x,board_render_y,SIZE_TILE * col ,SIZE_TILE * row };
    SDL_RenderFillRect(renderer, &rect);
}

void Board::show_board()
{
    for (int y = 0; y < row; ++y)
    {
        for (int x = 0; x < col; ++x)
        {
            if (board[y][x].has_ship())
                std::cout << " 1";
            else
                std::cout << " 0";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}