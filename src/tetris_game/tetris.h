#pragma once

#include <vector>
#include <stdexcept>
#include <SDL.h>
#include "tetris_config.h"
#include "pieces/piece.h"
#include "pieces/i_piece.h"
#include "pieces/o_piece.h"
#include "pieces/j_piece.h"
#include "pieces/t_piece.h"
#include "pieces/z_piece.h"
#include "pieces/s_piece.h"
#include "pieces/l_piece.h"

class Tetris {
private:
    enum Pieces {
        I, J, L, O, S, T, Z
    };

    unsigned int _last_time{0};

    int _width{800};
    int _height{1000};

    bool _running{false};

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    int _pixel_width_count = TetrisConfig::pixel_width_count;
    int _pixel_height_count = TetrisConfig::pixel_height_count;

    int _pixel_size{0};
    int _grid_width{0};
    int _grid_height{0};

    int _left_margin{0};
    int _top_margin{50};
    int _bottom_margin{50};

    SDL_Texture *_grid_texture;

    std::vector<Piece *> _pieces;

private:

    Piece *_create_piece(Pieces piece, int i, int j);

    void _init_tetris_grid();

    void _handle_events();

    void _move_pieces();

    void _draw_pieces();

public:

    Tetris();

    ~Tetris();

    void render();

    [[nodiscard]] inline bool is_running() const { return _running; }
};

