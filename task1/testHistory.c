#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "version.h"
#include "commit.h"



void free_history(struct history *history)
{
    if (history == NULL)
        return;

    struct commit *current = history->commit_list->next;
    struct commit *next;

    // Alle commits in der Liste freigeben
    while (current->next != history->commit_list)
    {
        next = current->next;
        free(current->comment);
        free(current);
        current = next;
    }

    free(current);
    free(history);
}

int main(int argc, char const *argv[])
{
    // Create a new history
    struct history *test_history = (struct history*)new_history("Circle of Life");

    // Add commits
    // Temporärer Speicher für den Kommentar
    char comment[50];
    for(int i = 0; i < 4; i++)
    {                   
        sprintf(comment, "Work %d", i + 1); // String erstellen mit "Work " und i+1
        struct commit *test_commit = new_commit(i+1, 0, i+1, comment);
        test_commit = add_minor_commit(test_history, test_commit, NULL);
    } 
    
    display_history(test_history);

    struct commit *test_commit = new_commit(5, 1, 0, "Release 1");
    test_commit = add_minor_commit(test_history, test_commit, NULL);
    test_commit = new_commit(6, 1, 1, "Work 1");
    test_commit = add_minor_commit(test_history, test_commit, NULL);
    test_commit = new_commit(7, 1, 2, "Work 2");
    test_commit = add_minor_commit(test_history, test_commit, NULL);
    test_commit = new_commit(8, 2, 0, "Release 2");
    test_commit = add_minor_commit(test_history, test_commit, NULL);
    test_commit = new_commit(9, 2, 1, "Work 1");
    test_commit = add_minor_commit(test_history, test_commit, NULL);

    display_history(test_history);

    test_commit = new_commit(10, 0, 5, "Security backport!!!");
    struct commit *after_commit = test_history->commit_list->next->next->next->next; // Insert after the 4th commit in history
    test_commit = add_minor_commit(test_history, test_commit, after_commit);

    display_history(test_history);

    // Searching for specific commit versions (Task 3 Question 5)
    infos(test_history, 1, 2);
    infos(test_history, 1, 7);
    infos(test_history, 4, 2);

    free_history(test_history);

    return 0;
}
