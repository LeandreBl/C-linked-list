#include "llist.h"

void llist_move_to_unused_node(llist_t *list, lnode_t *node)
{
  node->prev = NULL;
  node->next = list->unused;
  if (list->unused != NULL)
    list->unused->prev = node;
  list->unused = node;
  ++list->unused_size;
}

void llist_remove(llist_t *list, lnode_t *node)
{
  if (node == list->first)
    list->first = node->next;
  else if (node == list->last)
    list->last = node->prev;
  if (node->prev != NULL)
    node->prev->next = node->next;
  if (node->next != NULL)
    node->next->prev = node->prev;
  llist_move_to_unused_node(list, node);
  --list->size;
}
