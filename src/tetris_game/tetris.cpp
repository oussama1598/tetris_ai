#include "tetris.h"

Tetris::Tetris() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        throw std::runtime_error(SDL_GetError());

    _window = SDL_CreateWindow(
            "Tetris",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            SDL_WINDOW_ALLOW_HIGHDPI
    );

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == nullptr)
        throw std::runtime_error("Could not create a renderer");

    _running = true;
}

Tetris::~Tetris() {
//    SDL_DestroyTexture(texture_);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Tetris::_handle_events() {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            _running = false;
            break;
    }
}

void Tetris::render() {
    _handle_events();

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}
