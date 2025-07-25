#include "board.h"

SDL_Texture* Board::tile_hit = nullptr;
SDL_Texture* Board::tile_miss = nullptr;

Board::Board()
{
    // ��ʼ����ͼ
    tile_hit = ResourcesManager::instance()->get_texture(ResID::Tex_Tile_hit);
    tile_miss = ResourcesManager::instance()->get_texture(ResID::Tex_Tile_miss);

    // ��ʼ����������
    board.assign(row, std::vector<Tile>(col));
}

Board::~Board() = default;

void Board::on_render(SDL_Renderer* renderer)
{
    draw_board(renderer);

    EffectManager::instance()->on_render(renderer);

    // ��Ⱦ���и���״̬
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x) {
            SDL_Rect rect = {
                board_render_x + x * SIZE_TILE,
                board_render_y + y * SIZE_TILE,
                SIZE_TILE, SIZE_TILE
            };
            switch (board[y][x].get_status()) {
            case Tile::Status::Miss:
                SDL_RenderCopy(renderer, tile_miss, nullptr, &rect);
                break;
            case Tile::Status::Hit:
                SDL_RenderCopy(renderer, tile_hit, nullptr, &rect);
                break;
            default:
                break;
            }
        }
    }
}

void Board::on_update(double delta)
{
    std::cout << find_target;
    EffectManager::instance()->on_update(delta);//����

    if (find_target)
    {
        std::cout << "board find target" << std::endl;
        find_target = false;

        if (board[index_y][index_x].has_ship())
            EffectManager::instance()->show_effect(EffectID::Explosion, rect_explosion_target, 0, [this]()
                {
                    on_animation = false;
                    board[index_y][index_x].change_status(Tile::Status::Hit);
                    finish_hit = true;
                });
        else
            EffectManager::instance()->show_effect(EffectID::WaterSplash_single, rect_water_splash, 0,[this]()
                {
                    on_animation = false;
                    board[index_y][index_x].change_status(Tile::Status::Miss);
                    finish_hit = true;
                });
    }
}

void Board::on_input(const SDL_Event& event)
{
    on_mouse_move(event);

    if (on_animation) 
        return;

    on_mouse_click(event);
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
        int y = (event.button.y - board_render_y) / SIZE_TILE;

        if (x < 0 || x >= col || y < 0 || y >= row)
            return;

        index_x = x;
        index_y = y;
        mouse_click_tile_center =
        {
            board_render_x + x * SIZE_TILE + SIZE_TILE / 2,
            board_render_y + y * SIZE_TILE + SIZE_TILE / 2
        };

        auto status = board[y][x].get_status();

        if (status == Tile::Status::Unknown)
        {
            rect_select_target = {
                board_render_x + x * SIZE_TILE - 20,
                board_render_y + y * SIZE_TILE - 20,
                SIZE_TILE + 40, SIZE_TILE + 40
            };
            rect_water_splash = {
                board_render_x + x * SIZE_TILE - 20,
                board_render_y + y * SIZE_TILE,
                SIZE_TILE + 40, SIZE_TILE
            };
            rect_explosion_target = {
                board_render_x + x * SIZE_TILE - 20,
                board_render_y + y * SIZE_TILE - 40,
                SIZE_TILE + 40, SIZE_TILE + 40
            };

            EffectManager::instance()->show_effect(EffectID::SelectTarget, rect_select_target, 0, [this]()
                {
                    this->find_target = true;
                });

            on_animation = true;
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
    // ���̵�ɫ
    SDL_Rect board_rect =
    {
        board_render_x, board_render_y,
        col * SIZE_TILE, row * SIZE_TILE
    };
    SDL_SetRenderDrawColor(renderer, 30, 63, 102, 255);
    SDL_RenderFillRect(renderer, &board_rect);

    // ������
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 10, 55, 50, 120);
    // ����
    for (int i = 0; i <= col; ++i) 
    {
        int x = board_render_x + i * SIZE_TILE;
        SDL_RenderDrawLine(
            renderer, x, board_render_y, x,
            board_render_y + row * SIZE_TILE
        );
    }
    // ����
    for (int j = 0; j <= row; ++j) 
    {
        int y = board_render_y + j * SIZE_TILE;
        SDL_RenderDrawLine(
            renderer, board_render_x, y,
            board_render_x + col * SIZE_TILE, y
        );
    }
}

SDL_Point Board::place_ship(SDL_Point pos, int ship_size, bool is_horizontal)
{
    int x = (pos.x - board_render_x) / SIZE_TILE;
    int y = (pos.y - board_render_y) / SIZE_TILE;

    if ((pos.x-board_render_x) % SIZE_TILE > SIZE_TILE / 2)
        x++;

    if ((pos.y-board_render_y) % SIZE_TILE > SIZE_TILE / 2)
        y++;

    if (check_available(x,y, ship_size, is_horizontal))
    {
        if (is_horizontal)
        {
            for (int i = 0; i < ship_size; ++i)
            {
                board[y][x+i].place_ship();
            }
        }
        else
        {
            for (int i = 0; i < ship_size; ++i)
            {
                board[y + i][x].place_ship();
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


    // �����߽�����д����
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