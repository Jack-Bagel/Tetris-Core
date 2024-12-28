#pragma once
typedef struct Button {
    int x, y;
    char text[50];
    void (*on_press)();
} Button;

extern void *start_one_player();
