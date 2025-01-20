#pragma once
#define SAVE_FILE "../save.bin"

extern void register_IO_listeners();
extern int read_top_score(unsigned int *p_top_score, char* path);
extern int write_top_score(unsigned int top_score, char* path);
