#include "internal.h"

int llist_insert(llist_t *list, void *new_item, size_t position)
{
	lnode_t *new_node;
	lnode_t *node;

	if (position > list->size)
		return -1;
	else if (position == 0)
		return (llist_push_front(list, new_item));
	else if (position == list->size)
		return (llist_push_back(list, new_item));
	new_node = llist_pop_unused_node(list);
	if (new_node == NULL)
		return (-1);
	new_node->data = new_item;
	node = list->first;
	for (size_t i = 0; i < position - 1; ++i)
		node = node->next;
	new_node->prev = node;
	new_node->next = node->next;
	node->next->prev = new_node;
	node->next = new_node;
	++list->size;
	return (0);
}