#include "j_piece.h"

JPiece::JPiece(int i, int j) : Piece(i, j) {
    _color = {58, 120, 250, 255};

    _has_pivot = true;
    _pivot = {1, 1};

    _blocks = {
            {0, 0},
            {0, 1},
            {1, 1},
            {2, 1}
    };
}
