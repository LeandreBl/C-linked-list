#include "llist.h"
#include <stdio.h>
void *llist_pop_back(llist_t *list)
{
	void *data;

	if (list->size == 0)
		return (NULL);
	data = list->last->data;
	llist_remove(list, list->last);
	return (data);
}