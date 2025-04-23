#ifndef OFFSET_H
#define OFFSET_H
#include "version.h"

struct history; 

struct commit
{
    unsigned long id;       // 4 bytes
    struct version version; // 8 bytes
    char *comment;          // 8 bytes
    struct commit *next;    // 8 bytes
    struct commit *prev;    // 8 bytes
};

struct commit *new_commit(unsigned long id, unsigned short major, unsigned long minor, char *comment);

void printAdressesOfStructMembers(struct commit *commit);
 
struct commit *commit_of(struct version *version);

struct commit *add_minor_commit(struct history *history, struct commit *from, struct commit *after_commit);

struct commit *add_major_commit(struct history *history, struct commit *from, struct commit *after_commit);

#endif