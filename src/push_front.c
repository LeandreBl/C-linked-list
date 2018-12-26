#include "internal.h"

static void setup_node_place(llist_t *list, lnode_t *new_node)
{
  if (list->size != 0) {
    list->first->prev = new_node;
    new_node->next = list->first;
  }
  else {
    list->last = new_node;
    new_node->next = NULL;
  }
}

int llist_push_front(llist_t *list, void *new_item)
{
  lnode_t *new_node = llist_pop_unused_node(list);

  if (new_node == NULL)
    return (-1);
  setup_node_place(list, new_node);
  list->first = new_node;
  new_node->prev = NULL;
  new_node->data = new_item;
  ++list->size;
  return (0);
}