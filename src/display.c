#include "llist.h"

void llist_display(llist_t *list, void (*displayer)(void *data))
{
    lnode_t *node = list->first;

    while (node != NULL) {
        displayer(node);
        node = node->next;
    }
}