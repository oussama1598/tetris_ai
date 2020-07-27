#include "i_piece.h"

IPiece::IPiece(int i, int j) : Piece(i, j) {
    for (int k = -1; k < 3; ++k) {
        _blocks.push_back({0, k});
    }
}

void IPiece::rotate_left() {

}

void IPiece::rotate_right() {
    _blocks.clear();

    for (int k = -1; k < 3; ++k) {
        _blocks.push_back({k, 0});
    }
}
