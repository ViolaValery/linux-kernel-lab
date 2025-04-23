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

    struct commit *current = commit_of_list_head(history->commit_list->list_head.next);
    struct commit *next;

    // Alle Commits in der Liste freigeben
    while (current != history->commit_list)
    {
        next = commit_of_list_head(current->list_head.next);
        if (current->comment != NULL)
            free(current->comment);
        free(current);          
        current = next;
    }

    // Phantom-Commit freigeben
    if (history->commit_list->comment != NULL)
        free(history->commit_list->comment);
    free(history->commit_list);

    // History-Struktur freigeben
    free(history);
}

int main(int argc, char const *argv[])
{
    // Create a new history
    struct history *test_history = (struct history*)new_history("Circle of Life");

    if (test_history->commit_list == NULL || test_history->commit_list->list_head.next == NULL)
    {
        fprintf(stderr, "testHistory/main - list_head not initialized\n");
        return -1;
    }

    // Add commits
    struct commit *test_commit; 
    // Temporärer Speicher für den Kommentar
    char comment[50];
    for(int i = 0; i < 4; i++)
    {                   
        sprintf(comment, "Work %d", i + 1); // String erstellen mit "Work " und i+1
        test_commit = add_minor_commit(test_history, new_commit(i + 1, 0, i + 1, comment), NULL);
    } 
    
    display_history(test_history);

    test_commit = add_minor_commit(test_history, new_commit(5, 1, 0, "Release 1"), NULL);
    test_commit = add_minor_commit(test_history, new_commit(6, 1, 1, "Work 1"), NULL);
    test_commit = add_minor_commit(test_history, new_commit(7, 1, 2, "Work 2"), NULL);
    test_commit = add_minor_commit(test_history, new_commit(8, 2, 0, "Release 2"), NULL);
    test_commit = add_minor_commit(test_history, new_commit(9, 2, 1, "Work 1"), NULL);

    display_history(test_history);

    // Insert after the 4th commit in history
    struct commit *after_commit = commit_of_list_head((test_history->commit_list->list_head).next->next->next->next); 
    if(after_commit == NULL){
        fprintf(stderr, "testHistory/main - list_head not initialized");
    }
    test_commit = add_minor_commit(test_history, new_commit(10, 0, 5, "Security backport!!!"), after_commit);

    display_history(test_history);

    // Searching for specific commit versions (Task 3 Question 5)
    infos(test_history, 1, 2);
    infos(test_history, 1, 7);
    infos(test_history, 4, 2);

    free_history(test_history);

    return 0;
}
