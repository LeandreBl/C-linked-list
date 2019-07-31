#include "internal.h"

static lnode_t *find_from_first(llist_t *list, size_t position)
{
	lnode_t *node;

	for (node = list->first; position > 0; --position)
		node = node->next;
	return (node);
}

static lnode_t *find_from_last(llist_t *list, size_t position)
{
	lnode_t *node;

	position = list->size - position;
	for (node = list->last; position > 0; --position)
		node = node->prev;
	return (node);
}

static lnode_t *search_node(llist_t *list, size_t position)
{
	if (position > list->size / 2)
		return (find_from_last(list, position));
	return (find_from_first(list, position));
}

void llist_erase_at(llist_t *list, size_t position)
{
	lnode_t *deleted;

	if (position >= list->size)
		return;
	else if (position == 0) {
		llist_pop_front(list);
		return;
	}
	else if (position == list->size - 1) {
		llist_pop_back(list);
		return;
	}
	deleted = search_node(list, position);
	--list->size;
	deleted->prev->next = deleted->next;
	deleted->next->prev = deleted->prev;
	list->destructor(deleted->data);
	llist_move_to_unused_node(list, deleted);
}
