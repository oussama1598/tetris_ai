#pragma once

#include "pieces/piece.h"
#include "tetris_config.h"
#include <SDL.h>
#include <random>
#include <stdexcept>
#include <vector>

class Tetris {
private:
    unsigned int _last_time{0};

    int _width{800};
    int _height{1000};

    bool _running{false};

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    const int _pixel_width_count = TetrisConfig::pixel_width_count;
    const int _pixel_height_count = TetrisConfig::pixel_height_count;
    unsigned int _ascending_delay = TetrisConfig::ascending_delay;

    int _pixel_size{0};
    int _grid_width{0};
    int _grid_height{0};

    int _left_margin{0};
    int _top_margin{50};
    int _bottom_margin{50};

    SDL_Texture *_grid_texture{};

    std::vector<Piece *> _pieces;

    std::vector<std::vector<bool>> _grid{(size_t) _pixel_width_count,
                                         std::vector<bool>(_pixel_height_count)};

    std::random_device _rd;
    std::mt19937 _gen{_rd()};

    // distributions
    std::uniform_int_distribution<> _distribution{0, 6};
    std::uniform_int_distribution<> _x_distribution{0, _pixel_width_count - 1};


private:
    void _init_tetris_grid();

    Piece *_get_last_piece();

    void _handle_events();

    void _spawn_piece();

    void _move_pieces();

    void _draw_pieces();

public:
    Tetris();

    ~Tetris();

    void render();

    [[nodiscard]] inline bool is_running() const { return _running; }
};
