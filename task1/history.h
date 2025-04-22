#ifndef HISTORY_H
#define HISTORY_H

struct history
{
    unsigned long commit_count; // 8 bytes
    char *name; // 1 byte
    struct commit *commit_list; // 8 bytes
};

struct commit *new_commit(unsigned long id, unsigned short major, unsigned long minor, char *comment);

struct history *new_history(char *name, struct commit *commit_list);

struct commit *last_commit(struct history *history);

#endif