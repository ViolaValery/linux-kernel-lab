#include <stdlib.h>
#include <stdio.h>

#include "history.h"

/**
  * new_history - allocate, initialise and return a history
  *
  * @name: name of the history
  *
  * @return: a new history
  */
struct history *new_history(char *name)
{
	return NULL;
}

/**
  * last_commit - returns the last commit in the history
  *
  * @h: pointer to a history
  *
  * @return: the last commit in h
  */
struct commit *last_commit(struct history *h)
{
	return NULL;
}

/**
  * display_history - display the history, i.e., all the commits in the history
  *
  * @h: pointer to the history to display
  */
void display_history(struct history *h)
{
}

/**
  * infos - display the commit matching the major and minor numbers in history
  *         if it exists, "Not here!!!" otherwise
  *
  * @h: history to search
  * @major: major version of the commit to display
  * @minor: minor version of the commit to display
  */
void infos(struct history *h, int major, unsigned long minor)
{
}
