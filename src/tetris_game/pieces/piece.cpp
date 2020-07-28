#include "piece.h"

Piece::Piece(int i, int j) : _i(i), _j(j) {}

bool Piece::_out_of_bounds() {
    for (auto &block: _blocks) {
        int i = _i + block.i;
        int j = _j + block.j;

        if (i < 0 || i > (TetrisConfig::pixel_width_count - 1))
            return true;

        if (j < 0 || j > (TetrisConfig::pixel_height_count - 1))
            return true;
    }

    return false;
}

bool Piece::_piece_landed() const {
    for (auto &block: _blocks) {
        int j = _j + block.j;

        if (j == (TetrisConfig::pixel_height_count - 1)) return true;
    }

    return false;
}


void Piece::rotate_left() {

}

// reference https://www.codeproject.com/Articles/10668/Falling-Blocks-Board-and-Shape-Control
void Piece::rotate_right() {
    if (!_has_pivot || _moves_blocked)
        return;

    std::vector<Piece::position> temp_blocks;

    for (auto &block: _blocks) {
        temp_blocks.push_back({
                                      block.i - _pivot.i,
                                      block.j - _pivot.j
                              });
    }

    _blocks.clear();

    for (auto &temp_block: temp_blocks) {
        _blocks.push_back({
                                  temp_block.j + _pivot.i,
                                  -temp_block.i + _pivot.j
                          });
    }

    int min_x, max_x, min_y, max_y;

    min_x = _blocks[0].i;
    max_x = min_x;
    min_y = _blocks[0].j;
    max_y = min_y;

    for (auto &block: _blocks) {
        if (block.i < min_x) min_x = block.i;
        if (block.i > max_x) max_x = block.i;
        if (block.j < min_y) min_y = block.j;
        if (block.j > max_y) max_y = block.j;
    }

    _i = _i + min_x;
    _j = _j + min_y;

    _pivot = {
            _pivot.i - min_x,
            _pivot.j - min_y
    };

    for (auto &block: _blocks) {
        block.i = block.i - min_x;
        block.j = block.j - min_y;
    }
}

void Piece::move_down() {
    if (_moves_blocked) return;

    _j += 1;

    if (_out_of_bounds())
        _j -= 1;

    _moves_blocked = _piece_landed();
}

void Piece::move_left() {
    if (_moves_blocked) return;

    _i -= 1;

    if (_out_of_bounds())
        _i += 1;
}

void Piece::move_right() {
    if (_moves_blocked) return;

    _i += 1;

    if (_out_of_bounds())
        _i -= 1;
}
