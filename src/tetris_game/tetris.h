#pragma once

#include <stdexcept>
#include <SDL.h>

class Tetris {
private:
    int _width{800};
    int _height{600};

    bool _running{false};

    SDL_Window *_window;
    SDL_Renderer *_renderer;

private:

    void _handle_events();

public:

    Tetris();

    ~Tetris();

    void render();

    [[nodiscard]] inline bool is_running() const { return _running; }
};

