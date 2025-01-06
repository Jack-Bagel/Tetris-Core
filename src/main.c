#define SDL_MAIN_HANDLED
#include "GameWorld.h"

int main(int argc, char* argv[]) {

    initialize_game_world();
    run_game_world();
    exit_game_world();
}