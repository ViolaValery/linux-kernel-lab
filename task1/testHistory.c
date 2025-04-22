#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "version.h"
#include "commit.h"

void display_history(struct history *history)
{
    printf("History of '%s':\n", history->name);

    struct commit *commit = malloc(40);

    for (int i = 0; i < history->commit_count; i++)
    {
        commit = (struct commit*)(&history->commit_list + i); //i ist automatisch size 40
        printf("%ld: ", commit->id);
        display_version(&commit->version);
        printf("'%s'\n", commit->comment);
    }
}


int main(int argc, char const *argv[])
{
    // Create a new history
    struct history *test_history = (struct history*)new_history("Circle of Life");

    // Add commits
    for(int i = 0; i < 4; i++)
    {
        char *comment = "Work " + (i+1);
        struct commit *test_commit = new_commit(i+1, 0, i+1, comment);
        test_history = add_minor_commit(test_history, test_commit);
    }
    
    display_history(test_history); 
    return 0;
}
