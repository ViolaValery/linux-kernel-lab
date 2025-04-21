#include <stdlib.h>
#include <stdio.h>
#include <offset.h>

void printAdressesOfStructMembers(struct commit *commit)
{
    printf("Address of struct commit: %p\n", (void *)commit);
    printf("Address of id: %p\n", (void *)commit->id);
    printf("Address of version: %p\n", (void *)&commit->version);
    printf("Address of version.major: %p\n", (void *)&commit->version.major);
    printf("Address of version.minor: %p\n", (void *)&commit->version.minor);
    printf("Address of comment: %p\n", (void *)&commit->comment);
    printf("Address of next: %p\n", (void *)&commit->next);
    printf("Address of prev: %p\n", (void *)&commit->prev);
}

struct commit *commit_of(struct version *version)
{
    struct commit *commit = (struct commit *)((void *)version - (void *)offset_of(struct commit, version));
    return commit;
}