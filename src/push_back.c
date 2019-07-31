#include "internal.h"
#include <stdlib.h>

static void setup_node_place(llist_t *list, lnode_t *new_node)
{
	if (list->size != 0) {
		list->last->next = new_node;
		new_node->prev = list->last;
	}
	else {
		list->first = new_node;
		new_node->prev = NULL;
	}
}

int llist_push_back(llist_t *list, void *new_item)
{
	lnode_t *new_node = llist_pop_unused_node(list);

	if (new_node == NULL)
		return (-1);
	setup_node_place(list, new_node);
	list->last = new_node;
	new_node->next = NULL;
	new_node->data = new_item;
	++list->size;
	return (0);
}