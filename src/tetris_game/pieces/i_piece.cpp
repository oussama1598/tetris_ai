#include "i_piece.h"

IPiece::IPiece(int i, int j) : Piece(i, j) {
    _has_pivot = true;
    _pivot = {2, 0};

    for (int k = 0; k < 4; ++k) {
        _blocks.push_back({k, 0});
    }
}
