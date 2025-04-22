#include <stdio.h>
#include <stdlib.h>
#include "commit.h"

#define offset_of(type, member) \
    (&((type *)0)->member)



int main() {
 
    struct version *version_instance = (struct version*)malloc(sizeof(struct version));
    version_instance->minor = 0;
    version_instance->major = 1;
    struct commit *commit_instance = new_commit(52062, version_instance, "Initial commit", NULL, NULL);

    // Print the addresses of each member
    printAdressesOfStructMembers(commit_instance);

    printf("Offset between start of struct commit and its member version: %p\n", (void *)commit_of(&commit_instance->version));

    // Free the allocated memory
    free(new_commit);

    return 0;
}

