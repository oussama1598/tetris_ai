set(SOURCES tetris.cpp)

add_library(tetris_game ${SOURCES})
target_link_libraries(tetris_game CONAN_PKG::sdl2 CONAN_PKG::sdl2_image CONAN_PKG::sdl2_ttf)

add_executable(tetris_game_bin main.cpp)
target_link_libraries(tetris_game_bin PRIVATE tetris_game)
