#include "internal.h"

void *llist_get(llist_t *list, size_t position)
{
  lnode_t *node = llist_get_node_at(list, position);

  if (node == NULL)
    return (NULL);
  return (node->data);
}