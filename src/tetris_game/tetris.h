#pragma once

#include <vector>
#include <stdexcept>
#include <SDL.h>
#include "pieces/piece.h"

class Tetris {
private:
    int _width{800};
    int _height{1000};

    bool _running{false};

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    int _pixel_width_count{10};
    int _pixel_height_count{20};

    int _pixel_size{0};
    int _grid_width{0};
    int _grid_height{0};

    int _left_margin{0};
    int _top_margin{50};
    int _bottom_margin{50};

    SDL_Texture *_grid_texture;

    std::vector<Piece *> _pieces;

private:

    void _init_tetris_grid();

    void _handle_events();

    void _draw_pieces();

public:

    Tetris();

    ~Tetris();

    void render();

    [[nodiscard]] inline bool is_running() const { return _running; }
};

