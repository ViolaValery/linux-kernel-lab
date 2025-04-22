#include <stdio.h>
#include <stdlib.h>
#include "commit.h"
#include "history.h"

#define offset_of(type, member) \
    (&((type *)0)->member)



int main() {
    
    struct commit *commit_instance = new_commit(52062, 0, 1, "Initial commit");

    // Print the addresses of each member
    printAdressesOfStructMembers(commit_instance);

    printf("Offset between start of struct commit and its member version: %p\n", (void *)commit_of(&commit_instance->version));
    
    return 0;
}

