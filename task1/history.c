#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "version.h"
#include "commit.h"
#include "list.h"

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
    struct commit *phantom_commit = new_commit(0, 0, 0, "Phantom commit");
    if (phantom_commit == NULL)
    {
        fprintf(stderr, "new'_history - Initialisation of phantom commit failed.\n");
        free(history);
        return NULL;
    }
    INIT_LIST_HEAD(&phantom_commit->list_head);
    history->commit_list = phantom_commit;

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

    if (history->commit_list == NULL || history->commit_list->list_head.next == NULL)
    {
        fprintf(stderr, "last_commit - list_head.next is NULL\n");
        return NULL;
    }
    // Get the list_head of the last commit before the phantom commit
    struct list_head *list = history->commit_list->list_head.prev;
    // Calculate the offset to get pointer to the commmit containing the list_head
    return commit_of_list_head(list);
}

/**
 * display_history - display the history, i.e., all the commits in the history
 *
 * @h: pointer to the history to display
 */
void display_history(struct history *history)
{
    printf("History of '%s':\n", history->name);

    struct commit *commit = commit_of_list_head(history->commit_list->list_head.next);

    for (int i = 0; i < history->commit_count; i++)
    {
        printf("%ld: ", commit->id);
        display_version(&commit->version);
        printf("'%s'\n", commit->comment);
        commit = commit_of_list_head(commit->list_head.next);
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

    if (history == NULL || history->commit_list == NULL)
    {
        printf("History or commit_list is NULL\n");
        return 0;
    }

    struct commit *current_commit = commit_of_list_head(history->commit_list->list_head.next);

    // Durchlaufe die Liste der Commits
    for (int i = 0; i < history->commit_count; i++)
    {
        // Überprüfe, ob Major- und Minor-Version übereinstimmen
        if (current_commit->version.major == major && current_commit->version.minor == minor)
        {
            printf("%lu: ", current_commit->id);
            display_version(&current_commit->version);
            printf("'%s'\n", current_commit->comment);
            return 1;
        }

        // Zum nächsten Commit wechseln
        current_commit = commit_of_list_head(current_commit->list_head.next);
    }

    printf("Not here!!!\n");
    return 0;
}