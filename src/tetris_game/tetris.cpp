#include "tetris.h"

Tetris::Tetris() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        throw std::runtime_error(SDL_GetError());

    _window = SDL_CreateWindow(
            "Tetris",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            SDL_WINDOW_ALLOW_HIGHDPI);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == nullptr)
        throw std::runtime_error("Could not create a renderer");

    _running = true;

    _pixel_size = std::min((_height - _top_margin - _bottom_margin) / _pixel_height_count,
                           _width / _pixel_width_count);

    _grid_width = _pixel_size * _pixel_width_count;
    _grid_height = _pixel_size * _pixel_height_count;

    _left_margin = (_width - _grid_width) / 2;

    _init_tetris_grid();
}

Tetris::~Tetris() {
    //    for (auto &piece: _pieces)
    //        delete piece;

    SDL_DestroyTexture(_grid_texture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Tetris::_init_tetris_grid() {
    _grid_texture = SDL_CreateTexture(
            _renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            _grid_width, _grid_height);

    // to render to the texture instead of screen
    SDL_SetRenderTarget(_renderer, _grid_texture);

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 234, 234, 234, 255);

    for (int i = 1; i < _pixel_width_count; ++i) {
        SDL_RenderDrawLine(_renderer, _pixel_size * i, 0, _pixel_size * i, _grid_height);
    }

    for (int i = 1; i < _pixel_height_count; ++i) {
        SDL_RenderDrawLine(_renderer, 0, _pixel_size * i, _grid_width, _pixel_size * i);
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

    SDL_Rect rect{0, 0, _grid_width, _grid_height};
    SDL_RenderDrawRect(_renderer, &rect);

    SDL_SetRenderTarget(_renderer, nullptr);
}

Piece *Tetris::_get_last_piece() {
    return _pieces.at(_pieces.size() - 1);
}


void Tetris::_handle_events() {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            _running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    _get_last_piece()->rotate_right();
                    break;
                case SDLK_LEFT:
                    _get_last_piece()->move_left();
                    break;
                case SDLK_RIGHT:
                    _get_last_piece()->move_right();
                    break;
            }
            break;
    }
}

void Tetris::_spawn_piece() {
    if (_pieces.empty() || _get_last_piece()->is_landed()) {
        int random_piece_id = _distribution(_gen);

        auto *piece = new Piece(static_cast<Piece::Pieces>(random_piece_id), _x_distribution(_gen),
                                 0);
        piece->fix_out_of_bounds();

        _pieces.push_back(
                piece);
    }
}

void Tetris::_move_pieces() {
    unsigned int current_time = SDL_GetTicks();

    if (current_time - _last_time < _ascending_delay)
        return;


    for (auto &piece : _pieces) {
        piece->move_down(_grid);
    }

    _last_time = current_time;
}

void Tetris::_draw_pieces() {
    for (auto &column : _grid)
        std::fill(column.begin(), column.end(), false);

    for (auto &piece : _pieces) {
        int i = piece->get_i();
        int j = piece->get_j();

        SDL_Color color = piece->get_color();

        for (auto &block : piece->get_blocks()) {
            int block_i = i + block.i;
            int block_j = j + block.j;

            _grid[block_i][block_j] = true;

            SDL_Rect rect{
                    _pixel_size * block_i + _left_margin,
                    _pixel_size * block_j + _top_margin,
                    _pixel_size,
                    _pixel_size};

            SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(_renderer, &rect);

            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(_renderer, &rect);
        }
    }
}

void Tetris::render() {
    _handle_events();
    _spawn_piece();

    SDL_SetRenderDrawColor(_renderer, 241, 241, 241, 255);
    SDL_RenderClear(_renderer);

    SDL_Rect src = {0, 0, _grid_width, _grid_height};
    SDL_Rect dist = {_left_margin, _top_margin, _grid_width, _grid_height};
    SDL_RenderCopy(_renderer, _grid_texture, &src, &dist);

    _draw_pieces();
    _move_pieces();

    SDL_RenderPresent(_renderer);
}
