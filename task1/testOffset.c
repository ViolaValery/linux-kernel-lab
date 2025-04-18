#include <stdio.h>
#include <stdlib.h>
#include "testOffset.h"
#define offset_of(type, member) \
    (&((type *)0)->member)

// Forward declaration of the function
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

struct commit *commit_of(struct version *version){
    struct commit *commit = (struct commit *)((void *)version - (void *)offset_of(struct commit, version));
    return commit; 
}

int main() {

    // Allocate memory for a struct commit
    struct commit *new_commit = (struct commit *)malloc(sizeof(struct commit));
    if (new_commit == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the struct fields
    new_commit->id = 52062;
    new_commit->version.major = 1;
    new_commit->version.minor = 0;
    new_commit->comment = "Initial commit";
    new_commit->next = NULL;
    new_commit->prev = NULL;

    // Print the addresses of each member
    printAdressesOfStructMembers(new_commit);

    printf("Offset between start of struct commit and its member version: %p\n", (void *)commit_of(&new_commit->version));

    // Free the allocated memory
    free(new_commit);

    return 0;
}

