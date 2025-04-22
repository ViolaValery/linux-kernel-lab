#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "version.h"
#include "commit.h"

struct commit *new_commit(unsigned long id, unsigned short major, unsigned long minor, char *comment)
{
    struct commit *commit = (struct commit *)malloc(sizeof(struct commit));
    if (commit == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    commit->id = id;
    commit->version.major = major;
    commit->version.minor = minor;
    commit->version.flags = 0;
    commit->comment = (char*)strdup(comment); // TODO Why tho?
    commit->next = NULL; // Noch nicht eingegliedert 
    commit->prev = NULL;

    return commit;
}

// Creates a new (blank) history with an empty commit list
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

// Inserts a new commit into the list of history. After a specified after_commit OR at the end
static struct history *insert_commit(struct history *history, struct commit *commit, struct commit *after_commit)
{

    if (history->commit_list == NULL)
    {
        fprintf(stderr, "Inserting commit failed\n");
        return NULL;
    }

    struct commit *last;
    // When there is no commit specified, insert after last commit
    if (after_commit == NULL || after_commit == last_commit(history))
    {
        last = last_commit(history);
        commit->next = history->commit_list;
        history->commit_list->prev = commit; // First phantom commit points forward to the new commit
    }
    else
    {
        last = after_commit;
        commit->next = last->next;
    }

    last->next = commit;
    commit->prev = last;

    history->commit_count++;
    return history;

}

struct history *add_minor_commit(struct history *history, struct commit *commit, struct commit *after_commit)
{
    return insert_commit(history, commit, after_commit);
}

struct history *add_major_commit(struct history *history, struct commit *commit, struct commit *after_commit)
{
    return insert_commit(history, commit, after_commit);
}

// Iterates over a history to search for a specific commit version. If found, it should display the commit, else it should print "Not here!!!".
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