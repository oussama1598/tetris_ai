#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL_pixels.h>
#include "../tetris_config.h"

class Piece {
private:
    int _i{0};
    int _j{0};
    int _id{-1};

    std::vector<std::vector<int>> _grid;

    bool _moves_blocked{false};

public:
    enum Pieces {
        I,
        J,
        L,
        O,
        S,
        T,
        Z
    };

    struct position {
        int i;
        int j;
    };

protected:
    SDL_Color _color{255, 0, 0, 255};

    bool _has_pivot{false};
    position _pivot{};

    std::vector<position> _blocks;

private:
    bool _out_of_bounds();

    bool _has_collided();

    [[nodiscard]] bool _piece_landed() const;

public:
    Piece(Pieces piece, int id, std::vector<std::vector<int>> &grid, int i, int j);

    [[nodiscard]] inline int get_i() const { return _i; }

    [[nodiscard]] inline int get_j() const { return _j; }

    [[nodiscard]] inline int get_id() const { return _id; };

    [[nodiscard]] inline SDL_Color get_color() const { return _color; }

    inline std::vector<position> &get_blocks() { return _blocks; }

    [[nodiscard]] inline bool is_landed() const { return _moves_blocked; }

    void fix_out_of_bounds();

    void rotate_left();

    void rotate_right();

    void move_down();

    void move_left();

    void move_right();
};
