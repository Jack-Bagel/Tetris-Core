#include  "TetrisIO.h"
#include "EventListener.h"
#include "stdio.h"

static void save_top_score(void* event_data);
static EventListener save_top_score_event = {.callback = &save_top_score, .type = GAME_OVER_EVENT};


void register_IO_listeners() {
    sub_event_listener(&save_top_score_event);
}

int read_top_score(unsigned int *p_top_score, char* path) {
    FILE* p_file = fopen(path, "r");

    if (p_file == NULL) {
        printf("Error occured trying to open Top Score\n");
        return -1;
    }

    size_t result = fread(p_top_score, sizeof(int), 1, p_file);

    if (result != 1) {
        // write_top_score(0, SAVE_FILE);
    }

    fclose(p_file);
    return 0;
}


int write_top_score(unsigned int top_score, char* path) {
    FILE* p_file = fopen(path, "w");

    if (p_file == NULL) {
        printf("Error occured trying to open Top Score\n");
        return -1;
    }

    printf("TOP SCORE IS: %i \n", top_score);
    fwrite(&top_score, sizeof(int), 1, p_file);
    fclose(p_file);
    return 0;
}

static void save_top_score(void* event_data) {
    unsigned int top_score = *(unsigned int*) event_data;

    // Update Top Score
    // TODO: Make a game over event and add this
    unsigned int current_top_score;
    read_top_score(&current_top_score, SAVE_FILE);
    printf("current: %i\n", current_top_score);
    printf("top: %i\n", top_score);

    if (current_top_score < top_score) {
        write_top_score(top_score, SAVE_FILE);
    }
}
