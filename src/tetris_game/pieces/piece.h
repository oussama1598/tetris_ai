#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL_pixels.h>
#include "../tetris_config.h"

class Piece {
private:
    int _i{0};
    int _j{0};

    bool _moves_blocked{false};

public:
    struct position {
        int i;
        int j;
    };

protected:
    SDL_Color _color{255, 0, 0, 255};

    bool _has_pivot{false};
    position _pivot;

    std::vector<position> _blocks;

private:

    bool _out_of_bounds();

    bool _piece_landed() const;

public:

    Piece(int i, int j);

    [[nodiscard]] inline int get_i() const { return _i; }

    [[nodiscard]] inline int get_j() const { return _j; }

    [[nodiscard]] inline SDL_Color get_color() const { return _color; }

    inline std::vector<position> &get_blocks() { return _blocks; }

    virtual void rotate_left();

    virtual void rotate_right();

    virtual void move_down();

    virtual void move_left();

    virtual void move_right();
};

