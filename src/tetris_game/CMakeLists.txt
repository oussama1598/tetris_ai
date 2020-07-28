set(SOURCES
        tetris.cpp
        tetris.h

        pieces/piece.cpp
        pieces/piece.h

        pieces/i_piece.cpp
        pieces/i_piece.h

        pieces/o_piece.cpp
        pieces/o_piece.h

        pieces/j_piece.cpp
        pieces/j_piece.h

        pieces/t_piece.cpp
        pieces/t_piece.h

        pieces/z_piece.cpp
        pieces/z_piece.h

        pieces/s_piece.cpp
        pieces/s_piece.h

        pieces/l_piece.cpp
        pieces/l_piece.h

        tetris_config.cpp
        tetris_config.h)

add_library(tetris_game ${SOURCES})
target_link_libraries(tetris_game CONAN_PKG::sdl2 CONAN_PKG::sdl2_image CONAN_PKG::sdl2_ttf)

add_executable(tetris_game_bin main.cpp)
target_link_libraries(tetris_game_bin PRIVATE tetris_game)
