#include "t_piece.h"

TPiece::TPiece(int i, int j) : Piece(i, j) {
    _color = {72, 249, 251, 255};

    _has_pivot = true;
    _pivot = {1, 1};

    _blocks = {
            {1, 0},
            {1, 1},
            {0, 1},
            {2, 1}
    };
}
