#pragma once

#include <vector>
#include <SDL2/SDL_pixels.h>

class Piece {
private:
    struct position {
        int i;
        int j;
    };

    int _i{0};
    int _j{0};

    SDL_Color _color{255, 0, 0, 255};

protected:
    std::vector<position> _blocks;

public:
    Piece(int i, int j);

    [[nodiscard]] inline int get_i() const { return _i; }

    [[nodiscard]] inline int get_j() const { return _j; }

    [[nodiscard]] inline SDL_Color get_color() const { return _color; }

    inline std::vector<position> &get_blocks() { return _blocks; }

    virtual void rotate_left() = 0;

    virtual void rotate_right() = 0;
};

