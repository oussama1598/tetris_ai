#include "o_piece.h"

OPiece::OPiece(int i, int j) : Piece(i, j) {
    _color = {250, 232, 61, 255};

    _has_pivot = false;
    _blocks = {
            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1}
    };
}
