#include "piece.h"

Piece::Piece(Pieces piece, int id, std::vector<std::vector<int>> &grid, int i, int j)
    : _i(i), _j(j), _id(id), _grid(grid) {
    switch (piece) {
        case Pieces::I:
            _has_pivot = true;
            _pivot = {2, 0};

            for (int k = 0; k < 4; ++k) {
                _blocks.push_back({k, 0});
            }

            break;
        case Pieces::J:
            _color = {58, 120, 250, 255};

            _has_pivot = true;
            _pivot = {1, 1};

            _blocks = {
                    {0, 0},
                    {0, 1},
                    {1, 1},
                    {2, 1}};

            break;
        case Pieces::L:
            _color = {255, 172, 60, 255};

            _has_pivot = true;
            _pivot = {1, 1};

            _blocks = {
                    {0, 1},
                    {1, 1},
                    {2, 1},
                    {2, 0}};

            break;
        case Pieces::O:
            _color = {250, 232, 61, 255};

            _has_pivot = false;
            _blocks = {
                    {0, 0},
                    {1, 0},
                    {0, 1},
                    {1, 1}};

            break;
        case Pieces::S:
            _color = {238, 132, 253, 255};

            _has_pivot = true;
            _pivot = {1, 1};

            _blocks = {
                    {1, 0},
                    {1, 1},
                    {0, 1},
                    {2, 0}};

            break;
        case Pieces::T:
            _color = {72, 249, 251, 255};

            _has_pivot = true;
            _pivot = {1, 1};

            _blocks = {
                    {1, 0},
                    {1, 1},
                    {0, 1},
                    {2, 1}};

            break;
        case Pieces::Z:
            _color = {107, 227, 32, 255};

            _has_pivot = true;
            _pivot = {1, 1};

            _blocks = {
                    {0, 0},
                    {1, 0},
                    {1, 1},
                    {2, 1}};

            break;
    }
}

bool Piece::_out_of_bounds() {
    for (auto &block : _blocks) {
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
    return std::any_of(_blocks.begin(), _blocks.end(), [&](auto &block) {
        int j = _j + block.j;

        return j == (TetrisConfig::pixel_height_count - 1);
    });
}

bool Piece::_has_collided() {
    for (auto &block : _blocks) {
        int i = _i + block.i;
        int j = _j + block.j;

        if (_grid[i][j] != -1 && _grid[i][j] != _id) return true;
    }

    return false;
}


void Piece::fix_out_of_bounds() {
    int min_x = _blocks[0].i;
    int max_x = min_x;
    int min_y = _blocks[0].j;
    int max_y = min_y;

    for (auto &block : _blocks) {
        min_x = std::min(block.i, min_x);
        max_x = std::max(block.i, max_x);
        min_y = std::min(block.j, min_y);
        max_y = std::max(block.j, max_y);
    }

    if (_i < 0) {
        _i += -_i;
    }

    if ((_i + max_x) > (TetrisConfig::pixel_width_count - 1)) {
        _i = TetrisConfig::pixel_width_count - max_x - 1;
    }
}

void Piece::rotate_left() {
}

// reference https://www.codeproject.com/Articles/10668/Falling-Blocks-Board-and-Shape-Control
void Piece::rotate_right() {
    if (!_has_pivot || _moves_blocked)
        return;

    std::vector<Piece::position> temp_blocks;

    for (auto &block : _blocks) {
        temp_blocks.push_back({block.i - _pivot.i,
                               block.j - _pivot.j});
    }

    _blocks.clear();

    for (auto &temp_block : temp_blocks) {
        _blocks.push_back({temp_block.j + _pivot.i,
                           -temp_block.i + _pivot.j});
    }

    int min_x = _blocks[0].i;
    int max_x = min_x;
    int min_y = _blocks[0].j;
    int max_y = min_y;

    for (auto &block : _blocks) {
        min_x = std::min(block.i, min_x);
        max_x = std::max(block.i, max_x);
        min_y = std::min(block.j, min_y);
        max_y = std::max(block.j, max_y);
    }

    _i = _i + min_x;
    _j = _j + min_y;

    _pivot = {
            _pivot.i - min_x,
            _pivot.j - min_y};

    for (auto &block : _blocks) {
        block.i = block.i - min_x;
        block.j = block.j - min_y;
    }

    fix_out_of_bounds();
}

void Piece::move_down() {
    if (_moves_blocked) return;

    _j += 1;

    if (_out_of_bounds())
        _j -= 1;

    if (_has_collided()) {
        _j -= 1;

        _moves_blocked = true;

        return;
    }

    _moves_blocked = _piece_landed();
}

void Piece::move_left() {
    if (_moves_blocked) return;

    _i -= 1;

    if (_out_of_bounds())
        _i += 1;

    if (_has_collided())
        _i += 1;
}

void Piece::move_right() {
    if (_moves_blocked) return;

    _i += 1;

    if (_out_of_bounds())
        _i -= 1;

    if (_has_collided())
        _i -= 1;
}
void Piece::remove_block(int i, int j) {
    _blocks.erase(std::remove_if(_blocks.begin(), _blocks.end(), [&](position &block) {
                      int block_i = _i + block.i;
                      int block_j = _j + block.j;

                      return block_i == i && block_j == j;
                  }),
                  _blocks.end());
}
