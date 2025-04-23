#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commit.h"
#include "history.h"
#include "list.h"

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
    commit->comment = (char *)strdup(comment);
    if (commit->comment == NULL)
    {
        fprintf(stderr, "Memory allocation for comment failed\n");
        free(commit);
        return NULL;
    }

    // Initialize lists and major parent
    INIT_LIST_HEAD(&commit->list_head);
    INIT_LIST_HEAD(&commit->major_list);
    commit->major_parent = NULL;

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
static struct commit *insert_commit(struct history *history, struct commit *commit, struct commit *after)
{

    if (history->commit_list == NULL)
    {
        fprintf(stderr, "Inserting commit failed\n");
        return NULL;
    }

    // When there is no commit specified, insert after last commit
    if (after == NULL || after == last_commit(history))
    {
        after = last_commit(history);
        if (after == NULL)
        {
            fprintf(stderr, "insert_commit - Initialisation of phantom commit failed.\n");
            return NULL;
        }
        list_add(&(commit->list_head), &(after->list_head));
    }
    else
    {
        list_add(&commit->list_head, &after->list_head);
    }

    history->commit_count++;
    return commit;
}

struct commit *add_minor_commit(struct history *history, struct commit *from, struct commit *after_commit)
{
    return insert_commit(history, from, after_commit);
}

struct commit *add_major_commit(struct history *history, struct commit *from, struct commit *after_commit)
{
    if (from == NULL)
    {
        fprintf(stderr, "add_major_commit - Major parent commit is NULL\n");
        return NULL;
    }

    // Set major parent of this new commit
    from->major_parent = after_commit;

    // Add this commit to the major_list
    list_add_tail(&from->major_list, &after_commit->major_list);

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
    printf("Address of next: %p\n", (void *)&commit->list_head.next);
    printf("Address of prev: %p\n", (void *)&commit->list_head.prev);
}

struct commit *commit_of_version(struct version *version)
{
    struct commit *commit = (struct commit *)((void *)version - offsetof(struct commit, version));
    return commit;
}

struct commit *commit_of_list_head(struct list_head *list)
{
    // Calculate the offset to get pointer to the commmit containing the list_head
    return (struct commit *)((char *)list - offsetof(struct commit, list_head));
}

int *del_commit(struct commit *victim){

    return 0;
}
