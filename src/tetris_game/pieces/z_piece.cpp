#include "z_piece.h"

ZPiece::ZPiece(int i, int j) : Piece(i, j) {
    _color = {107, 227, 32, 255};

    _has_pivot = true;
    _pivot = {1, 1};

    _blocks = {
            {0, 0},
            {1, 0},
            {1, 1},
            {2, 1}
    };
}
