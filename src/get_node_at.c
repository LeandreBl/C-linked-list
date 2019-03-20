#include "internal.h"

static lnode_t *get_from_last(llist_t *list, size_t position)
{
  lnode_t *node;

  node = list->last;
  for (size_t i = 0; i < position - 1; ++i)
    node = node->prev;
  return (node);
}

static lnode_t *get_from_first(llist_t *list, size_t position)
{
  lnode_t *node;

  node = list->first;
  for (size_t i = 0; i < position; ++i)
    node = node->next;
  return (node);
}

__attribute__ ((visibility ("hidden"))) lnode_t *llist_get_node_at(llist_t *list, size_t position)
{
  if (position >= list->size)
    return (NULL);
  else if (position == list->size - 1)
    return (list->last);
  else if (position == 0)
    return (list->first);
  else if (position < list->size / 2)
    return (get_from_first(list, position));
  return (get_from_last(list, list->size - position));
}