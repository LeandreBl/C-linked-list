#include "llist.h"

void *llist_pop_front(llist_t *list)
{
	void *data;

	if (list->size == 0)
		return (NULL);
	data = list->first->data;
	llist_remove(list, list->first);
	return (data);
}