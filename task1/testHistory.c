#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "version.h"
#include "commit.h"

display_history(struct history *history)
{
    printf("History of '%s':\n", history->name);

    struct commit *commit = malloc(40);

    for (int i = 0; i < history->commit_count; i++)
    {
        commit = (struct commit*)(&history->commit_list + i); //i ist automatisch size 40
        printf("%d: ", (i + 1));
        display_version(&commit->version);
        printf("'%s'\n", commit->comment);
    }
}


int main(int argc, char const *argv[])
{
    //display_history(); 
    return 0;
}
