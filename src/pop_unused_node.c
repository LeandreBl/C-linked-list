#include "llist.h"

lnode_t *llist_pop_unused_node(llist_t *list)
{
  lnode_t *node;

  if (list->unused_size == 0 && llist_reserve(list, list->unused_size + REALLOC_POOL) == -1)
    return (NULL);
  node = list->unused;
  list->unused = list->unused->next;
  if (list->unused)
    list->unused->prev = NULL;
  --list->unused_size;
  return (node);
}