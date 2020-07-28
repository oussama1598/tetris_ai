#pragma once


#include "piece.h"

class OPiece : public Piece {
public:
    OPiece(int i, int j);

    void rotate_right() override {};

    void rotate_left() override {};
};

