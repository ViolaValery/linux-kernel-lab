#ifndef OFFSET_H
#define OFFSET_H
#include "version.h"

struct commit
{
    unsigned long id;       // 4 bytes
    struct version version; // 8 bytes
    char *comment;          // 8 bytes
    struct commit *next;    // 8 bytes
    struct commit *prev;    // 8 bytes
};

void printAdressesOfStructMembers(struct commit *commit);

struct commit *commit_of(struct version *version);

#endif