#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "version.h"
#include "offset.h"

struct commit *new_commit(unsigned long id, unsigned short major, unsigned long minor, char *comment)
{
    struct commit *commit = (struct commit *)malloc(40);
    if (commit == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    commit->id = id;
    commit->version.major = major;
    commit->version.minor = minor;
    commit->comment = comment;
    commit->next = NULL;
    commit->prev = NULL;

    return commit;
}

// Creates a new (blank) histopry with an empty commit list
struct history *new_history(char *name)
{
    struct history *history = (struct history*)malloc(24);
    if (history == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    history->commit_count = 0;
    history->name = name;
    history->commit_list = &history->commit_list;
    return history;
}

struct commit *last_commit(struct history *history)
{
    return history->commit_list;
}

static struct history *insert_commit(struct history *history, struct commit *commit)
{
    history->commit_count++;

    if (history->commit_list == NULL)
    {
        history->commit_list = commit;
        return history;
    }

    struct commit *last = last_commit(history);
    last->next = commit;
    commit->prev = last;
    
    return history;
}

static struct history *add_minor_commit(struct history *history, struct commit *commit)
{
    return insert_commit(history, commit);
}

static struct history *add_ajor_commit(struct history *history, struct commit *commit)
{
    return insert_commit(history, commit);
}

