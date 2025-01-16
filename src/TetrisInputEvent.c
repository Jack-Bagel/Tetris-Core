#include "TetrisInputEvent.h"
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>

extern bool is_running;
void (*handle_event)(TetrisBoard[2], SDL_Event *);

void update_event(TetrisBoard p_tetris_board[2]) {
    SDL_Event current_event;

    while (SDL_PollEvent(&current_event) != 0) {

        // Handles all events
        handle_event(p_tetris_board, &current_event);

        // Handles things like ALT + F4
        switch (current_event.type) {
            case SDL_QUIT:
                is_running = false;
            break;
        }
    }
}
