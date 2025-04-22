#ifndef HISTORY_H
#define HISTORY_H
#include "version.h"

struct history
{
    unsigned long commit_count; // 8 bytes
    char *name; // 1 byte
    struct commit *commit_list; // 8 bytes
};

struct commit *new_commit(unsigned long id, unsigned short major, unsigned long minor, char *comment);

struct history *new_history(char *name);

struct commit *last_commit(struct history *history);

struct history *add_minor_commit(struct history *history, struct commit *commit, struct commit *after_commit);

struct history *add_major_commit(struct history *history, struct commit *commit, struct commit *after_commit);

int infos(struct history *history, unsigned short major, unsigned long minor);

#endif