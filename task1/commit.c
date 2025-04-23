#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commit.h"
#include "history.h"

// Macro to calculate the offset of a member within a struct
#define offset_of(type, member) ((size_t) &(((type *)0)->member))

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
    commit->comment = (char *)strdup(comment); // TODO Why tho?
    commit->next = NULL;                       // Noch nicht eingegliedert
    commit->prev = NULL;

    return commit;
}

/**
 * insert_commit - Inserts a new commit into the list of history. After a specified after_commit OR at the end.
 * 
 * @from: commit that will be the predecessor of the new one
 * @new: commit to be inserted after from
 *
 * @return: a pointer to the newly inserted commit
 */
static struct commit *insert_commit(struct history *history, struct commit *commit, struct commit *after_commit)
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
    return commit;
}

struct commit *add_minor_commit(struct history *history, struct commit *from, struct commit *after_commit)
{
    return insert_commit(history, from, after_commit);
}

struct commit *add_major_commit(struct history *history, struct commit *from, struct commit *after_commit)
{
    return insert_commit(history, from, after_commit);
}

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
