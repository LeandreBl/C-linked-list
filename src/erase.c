#include "llist.h"

void llist_erase(llist_t *list, void *data_to_delete)
{
  for (lnode_t *node = list->first; node != NULL; node = node->next) {
    if (node->data == data_to_delete) {
      list->destructor(node->data);
      llist_remove(list, node);
      return;
    }
  }
}
