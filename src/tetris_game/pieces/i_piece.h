#pragma once

#include "piece.h"

class IPiece : public Piece {
public:
    IPiece(int i, int j);

    void rotate_left() override;

    void rotate_right();
};

