#include "s_piece.h"

SPiece::SPiece(int i, int j) : Piece(i, j) {
    _color = {238, 132, 253, 255};

    _has_pivot = true;
    _pivot = {1, 1};

    _blocks = {
            {1, 0},
            {1, 1},
            {0, 1},
            {2, 0}
    };
}
