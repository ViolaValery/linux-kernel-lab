#ifndef COMMIT_H
#define COMMIT_H
#include "list.h"
#include "version.h"

struct history;

struct commit
{
    unsigned long id;       // 4 bytes
    struct version version; // 8 bytes
    char *comment;          // 8 bytes
    struct list_head list_head;
};

struct commit *new_commit(unsigned long id, unsigned short major, unsigned long minor, char *comment);

void printAdressesOfStructMembers(struct commit *commit);
 
struct commit *commit_of_version(struct version *version);

struct commit *commit_of_list_head(struct list_head *list_head);

struct commit *add_minor_commit(struct history *history, struct commit *from, struct commit *after_commit);

struct commit *add_major_commit(struct history *history, struct commit *from, struct commit *after_commit);

int *del_commit(struct commit *victim);

#endif