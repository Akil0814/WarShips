#include "board.h"
#include <cmath>

SDL_Texture* Board::tile_hit = nullptr;
SDL_Texture* Board::tile_miss = nullptr;
SDL_Texture* Board::tile_detected = nullptr;
SDL_Texture* Board::tile_defance = nullptr;
SDL_Texture* Board::tile_select = nullptr;
SDL_Texture* Board::tile_sink = nullptr;
SDL_Texture* Board::tex_hand = nullptr;
SDL_Texture* Board::tex_set_target = nullptr;


Board::Board()
{
    board.assign(row, std::vector<Tile>(col));

    tile_hit = ResourcesManager::instance()->get_texture(ResID::Tex_Tile_hit);
    tile_miss= ResourcesManager::instance()->get_texture(ResID::Tex_Tile_miss);
    tile_detected = ResourcesManager::instance()->get_texture(ResID::Tex_Tile_unknow);
    tile_defance= ResourcesManager::instance()->get_texture(ResID::Tex_Tile_defance);
    tile_sink = ResourcesManager::instance()->get_texture(ResID::Tex_Tile_sink);
    tile_select = ResourcesManager::instance()->get_texture(ResID::Tex_Tile_select);
    tex_set_target = ResourcesManager::instance()->get_texture(ResID::Tex_SetTarget);

}

Board::~Board() = default;

void Board::on_render(SDL_Renderer* renderer)
{
    draw_board(renderer);
    show_atk_feasibility(renderer, mouse_pos);

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
            case Tile::Status::Detected:
                SDL_RenderCopy(renderer, tile_detected, nullptr, &rect);
                break;

            case Tile::Status::Miss:
                SDL_RenderCopy(renderer, tile_miss, nullptr, &rect);
                break;

            case Tile::Status::Hit:
                SDL_RenderCopy(renderer, tile_hit, nullptr, &rect);
                break;

            case Tile::Status::Defend:
                SDL_RenderCopy(renderer, tile_defance, nullptr, &rect);
                break;

            case Tile::Status::Sink:
                SDL_RenderCopy(renderer, tile_sink, nullptr, &rect);
                break;

            default:
                break;
            }
        }
    }

    EffectManager::instance()->on_render(renderer);
    BulletManager::instance()->on_render(renderer);

    if (move_in_board)
    {

        SDL_Rect set_target_rect = {
             mouse_pos.x-13, mouse_pos.y-13,
             26,26};

        SDL_RenderCopy(renderer, tex_set_target, nullptr, &set_target_rect);
    }
}

void Board::on_update(double delta,SkillType& current_skill)
{
    EffectManager::instance()->on_update(delta);//局内
    BulletManager::instance()->on_update(delta);
    this->skill_using = current_skill;
}

void Board::on_input(const SDL_Event& event)
{
    on_mouse_move(event);
    on_mouse_click(event);
}

void Board::on_mouse_move(const SDL_Event& event)
{
    if (is_inside(event.motion.x, event.motion.y))
    {
        move_in_board = true;
        mouse_pos.x = event.motion.x;
        mouse_pos.y = event.motion.y;
        SDL_ShowCursor(SDL_DISABLE);
    }
    else
    {
        move_in_board = false;
        SDL_ShowCursor(SDL_ENABLE);
    }
}

void Board::on_mouse_click(const SDL_Event& event)
{
    if (!is_inside(event.button.x, event.button.y)|| skill_using ==SkillType::NONE)
        return;

    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT )
    {
        if (!can_take_action)
        {
            Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound(ResID::Sound_Fail_Fire), 0);
            return;
        }

        start_action = true;
        ++action_time;
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

        switch (skill_using)
        {
        case SkillType::NONE:
            break;
        case SkillType::Missile:
        case SkillType::Attack_5C:
        case SkillType::Attack_3x3:
            EffectManager::instance()->show_effect(EffectID::SelectTarget, rect_select_target, 0, [](){});
            BulletManager::instance()->fire(mouse_click_tile_center, this, { index_x, index_y }, skill_using);
            ++total_atk_time;
            break;

        case SkillType::Detect_3x3:
        case SkillType::Detect_13C:
            detect_board(skill_using, { index_x, index_y });
            break;
        case SkillType::Repair:
            break;
        default:
            break;
        }   
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
        ship->update_in_board_pos({ x,y });
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
        //show_board();
}

void Board::ship_sink(SDL_Point pos, int ship_size, bool is_horizontal)
{
    if (is_horizontal)
    {
        for (int i = 0; i < ship_size; ++i)
        {
            board[pos.y][pos.x + i].change_status(Tile::Status::Sink);
        }
    }
    else
    {
        for (int i = 0; i < ship_size; ++i)
        {
            board[pos.y + i][pos.x].change_status(Tile::Status::Sink);
        }
    }
    //show_board();
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

void Board::show_atk_feasibility(SDL_Renderer* renderer, SDL_Point pos)
{
    if (!move_in_board)
        return;

    SDL_Point grid_pos = { 0 };

    if (pos.x - board_render_x < -(SIZE_TILE / 2) || pos.y - board_render_y < -(SIZE_TILE / 2))
    {
        int g_pos_x = std::floor(double(pos.x - board_render_x) / SIZE_TILE);
        int g_pos_y = std::floor(double(pos.y - board_render_y) / SIZE_TILE);

        grid_pos = { g_pos_x,g_pos_y };
    }
    else
    {
        grid_pos =
        {
            (pos.x - board_render_x) / SIZE_TILE,
            (pos.y - board_render_y) / SIZE_TILE
        };
    }
    SDL_Rect rect;

    std::vector<SDL_Rect> highlight_rects;

    auto add_rect = [&](int gx, int gy) {
        if (gx < 0 || gx >= col || gy < 0 || gy >= row) return;
        highlight_rects.push_back
        ({
            board_render_x + gx * SIZE_TILE,
            board_render_y + gy * SIZE_TILE,
            SIZE_TILE,
            SIZE_TILE
            });
        };

    switch (skill_using)
    {
    case SkillType::NONE:
        // nothing
        break;
    case SkillType::Missile:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 50);
        add_rect(grid_pos.x, grid_pos.y);
        break;
    case SkillType::Repair:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 50);
        add_rect(grid_pos.x, grid_pos.y);
        break;
    case SkillType::Attack_3x3:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 50);
        for (int j = grid_pos.y - 1; j <= grid_pos.y + 1; ++j)
            for (int i = grid_pos.x - 1; i <= grid_pos.x + 1; ++i)
                add_rect(i, j);
        break;
    case SkillType::Detect_3x3:
        SDL_SetRenderDrawColor(renderer, 50, 255, 255, 50);
        for (int j = grid_pos.y - 1; j <= grid_pos.y + 1; ++j)
            for (int i = grid_pos.x - 1; i <= grid_pos.x + 1; ++i)
                add_rect(i, j);
        break;
    case SkillType::Detect_13C:
        SDL_SetRenderDrawColor(renderer, 50, 255, 255, 50);
        // 中心 3×3
        for (int j = grid_pos.y - 1; j <= grid_pos.y + 1; ++j)
            for (int i = grid_pos.x - 1; i <= grid_pos.x + 1; ++i)
                add_rect(i, j);
        // 上下左右再多一格
        add_rect(grid_pos.x - 2, grid_pos.y);
        add_rect(grid_pos.x + 2, grid_pos.y);
        add_rect(grid_pos.x, grid_pos.y - 2);
        add_rect(grid_pos.x, grid_pos.y + 2);
        break;
    case SkillType::Attack_5C:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 50);   // 半透明红
        add_rect(grid_pos.x, grid_pos.y);     // 中心
        add_rect(grid_pos.x - 1, grid_pos.y);     // 左
        add_rect(grid_pos.x + 1, grid_pos.y);     // 右
        add_rect(grid_pos.x, grid_pos.y - 1); // 上
        add_rect(grid_pos.x, grid_pos.y + 1); // 下
        break;
    default:
        break;
    }

    // 真正绘制
    for (auto& r : highlight_rects) {
        SDL_RenderCopy(renderer, tile_select, nullptr, &r);
        SDL_RenderFillRect(renderer, &r);
    }
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

void Board::show_board(int x)
{
    for (int y = 0; y < row; ++y)
    {
        for (int x = 0; x < col; ++x)
        {

                std::cout <<static_cast<int>(board[y][x].get_status())<<" ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Board::is_on_animation()
{
    return on_animation;
}

int Board::get_atk_time_on_board()const
{
    return total_atk_time;
}

std::vector<std::vector<Tile>>& Board::get_tile_board()
{
    return board;
}


void Board::detect_board(SkillType type, SDL_Point c)
{
    auto apply = [&](int i, int j)
    {
            if (i < 0 || i >= col || j < 0 || j >= row)
                return;
        auto& tile = board[j][i];
        if (tile.has_ship()&& tile.get_status()==Tile::Status::Unknown)
        {
            if (auto* ship = tile.get_ship_on_tile(); ship && ship->can_detect())
            {
                tile.change_status(Tile::Status::Detected);
            }
        }
    };

    if (type == SkillType::Detect_3x3) {
        for (int j = c.y - 1; j <= c.y + 1; ++j)
            for (int i = c.x - 1; i <= c.x + 1; ++i)
                apply(i, j);

        return;
    }

    if (type == SkillType::Detect_13C)
    {
        for (int j = c.y - 1; j <= c.y + 1; ++j)
            for (int i = c.x - 1; i <= c.x + 1; ++i)
                apply(i, j);

        apply(c.x - 2, c.y);
        apply(c.x + 2, c.y);
        apply(c.x, c.y - 2);
        apply(c.x, c.y + 2);

        return;
    }
}




void Board::if_can_take_action(bool can)
{
    can_take_action = can;
}

bool Board::have_action()
{
    return start_action;
}

int Board::get_action_time()
{
    return action_time;
}

void Board::reset_action_time()
{
    action_time = 0;
}
