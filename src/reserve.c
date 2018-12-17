#include <stdlib.h>
#include <string.h>

#include "llist.h"

static int add_unused_node(llist_t *list)
{
	lnode_t *new_node = malloc(sizeof(lnode_t));

	if (list->unused != NULL) {
		list->unused->prev = new_node;
		if (list->unused->prev == NULL)
			return (-1);
		list->unused->prev = new_node;
		new_node->next = list->unused;
		list->unused = new_node;
	}
	else {
		list->unused = new_node;
		memset(new_node, 0, sizeof(*new_node));
	}
	list->unused->data = NULL;
	++list->unused_size;
	return (0);
}

int llist_reserve(llist_t *list, size_t reserve_size)
{
	size_t new_size;

	if (reserve_size <= list->unused_size)
		return (0);
	new_size = reserve_size - list->unused_size;
	for (size_t i = 0; i < new_size; ++i)
		if (add_unused_node(list) == -1)
			return (-1);
	return (0);
}