#include "l_piece.h"

LPiece::LPiece(int i, int j) : Piece(i, j) {
    _color = {255, 172, 60, 255};

    _has_pivot = true;
    _pivot = {1, 1};

    _blocks = {
            {0, 1},
            {1, 1},
            {2, 1},
            {2, 0}
    };
}
