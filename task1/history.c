#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "version.h"
#include "commit.h"



/**
 * new_history - Creates a new (blank) history with an empty commit list
 *
 * @name: name of the history
 *
 * @return: a new history
 */
struct history *new_history(char *name)
{
    struct history *history = (struct history*)malloc(sizeof(struct history));
    if (history == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    history->commit_count = 0;
    history->name = name;
    // Phantom comit, that points to itself (Task 3 Question 2)
    history->commit_list = (struct commit*)malloc(sizeof(struct commit));
    history->commit_list->next = history->commit_list;
    history->commit_list->prev = history->commit_list;
    return history;
}

struct commit *last_commit(struct history *history)
{
    if (history == NULL || history->commit_list == NULL)
    {
        fprintf(stderr, "History or commit_list NULL\n");
        return NULL;
    }

    if (history->commit_count == 0)
    {
        return history->commit_list;
    }

    return history->commit_list->prev; // Last commit is the one before the phantom commit
}

/**
 * display_history - display the history, i.e., all the commits in the history
 *
 * @h: pointer to the history to display
 */
void display_history(struct history *history)
{
    printf("History of '%s':\n", history->name);

    struct commit *commit = history->commit_list;

    for (int i = 0; i < history->commit_count; i++)
    {
        commit = commit->next;
        printf("%ld: ", commit->id);
        display_version(&commit->version);
        printf("'%s'\n", commit->comment);
    }
    printf("\n");
}

/**
 * infos - display the commit matching the major and minor numbers in history
 *         if it exists, "Not here!!!" otherwise
 *
 * @h: history to search
 * @major: major version of the commit to display
 * @minor: minor version of the commit to display
 */
int infos(struct history *history, unsigned short major, unsigned long minor)
{
    printf("Searching for commit %us.%lu :  ", major, minor);
    struct commit* current_commit = history->commit_list->next;

    for(int i = 0; i < history->commit_count; i++)
    {
        // Commit found?
        if (current_commit->version.major == major && current_commit->version.minor == minor)
        {
            printf("%lu: ", current_commit->id);
            display_version(&current_commit->version);
            printf("'%s'", current_commit->comment);
            printf("\n");
            return 1;
        }
            
        // Cut of the search process if the major version is already greater than the one looked for
        if (current_commit->version.major >= major && current_commit->version.minor > minor)
        {
            printf("Not here!!!\n");
            return 0;
        }

        current_commit = current_commit->next;
    }
    printf("Not here!!!\n");
    return 0;
}