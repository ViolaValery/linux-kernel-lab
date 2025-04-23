#ifndef HISTORY_H
#define HISTORY_H
#include "version.h"

struct history
{
    unsigned long commit_count; // 8 bytes
    char *name; // 1 byte
    struct commit *commit_list; // 8 bytes
};


struct history *new_history(char *name);

struct commit *last_commit(struct history *history);

void display_history(struct history *history);

int infos(struct history *history, unsigned short major, unsigned long minor);

#endif