#include <stdlib.h>
#include <string.h>

#include "llist.h"

static void default_initializer(llist_t *list, size_t default_len,
                                void (*default_destructor)(void *))
{
  list->size = 0;
  list->unused_size = default_len;
  list->first = NULL;
  list->last = NULL;
  list->destructor = default_destructor;
}

int llist_create(llist_t *list, size_t default_len,
                 void (*default_destructor)(void *))
{
  lnode_t *node;

  if (default_len == 0) {
    memset(list, 0, sizeof(*list));
    return (0);
  }
  node = malloc(sizeof(*node));
  if (node == NULL)
    return (-1);
  default_initializer(list, default_len, default_destructor);
  node->prev = NULL;
  list->unused = node;
  while (default_len > 1) {
    node->next = malloc(sizeof(*node));
    if (node->next == NULL)
      return (-1);
    node->data = NULL;
    node->next->prev = node;
    node = node->next;
    --default_len;
  }
  node->next = NULL;
  node->data = NULL;
  return (0);
}

void llist_destroy(llist_t *list)
{
  lnode_t *node = list->first;
  lnode_t *prev;

  while (node != NULL) {
    if (list->destructor != NULL)
      list->destructor(node->data);
    prev = node;
    node = node->next;
    free(prev);
  }
  node = list->unused;
  while (node != NULL) {
    prev = node;
    node = node->next;
    free(prev);
  }
}